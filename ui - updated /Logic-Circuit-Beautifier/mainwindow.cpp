#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QProcess>
#include <QString>

#include "DAG.h"
#include "gate.h"
#include "TopoSort.h"

QString VerilogFileName;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    // BROWSE

   VerilogFileName = QFileDialog :: getOpenFileName(
                this,
                tr("Choose File"),                              // Dialog Name
                "//",                                           // path starts from root
                "All files (*.txt)"                              // shows only .v files (i.e. Verilog files)
                );

    ui->textBrowser->setText(VerilogFileName);                  // displays path of file in the text browser
}

void MainWindow::on_pushButton_clicked()
{
    QFileInfo filePath(VerilogFileName);
    QString fileName = filePath.fileName();

    // RUN

    /*
    QString program = "/Users/mac/Library/Developer/Xcode/DerivedData/CSCE337Project1-groosmpjonvudfaudxeyovpzjfoy/Build/Products/Debug/CSCE337Project1";
    QProcess process;
    process.startDetached(program, QStringList() << fileName);
    */

    /**/

    DAG netlist;
    gate * g, * g1;

    //string file = "//Users//mac//Desktop//folder//parsed_booth.g.v.txt";
    //string file = argv[1];

    unsigned int numberGates;

    //if (netlist->openFile(argv[1]))
    if (netlist.readFile(VerilogFileName))
    {
        //netlist.readFile();
        numberGates = netlist.getGatesCounter();

        netlist.adjMatrix.resize(numberGates);
        for (qint16 i = 0; i < numberGates; i++)
            netlist.adjMatrix[i].resize(numberGates);

        for (qint16 i = 0; i < numberGates; i++)
        {
            g = &(netlist.gates[i]);

            for (qint16 j = 0; j < g->inputs.size(); j++)          // for each input
            {
                // check if the each input of the gate is an output of another gate
                int outin = netlist.find(&(netlist.outputs),g->inputs[j]);

                for (qint16 k = 0; k < numberGates; k++)   // for each output
                {
                    g1 = &(netlist.gates[k]);
                    if (outin!= -1)
                        if (g1->output == netlist.outputs[outin])
                            netlist.adjMatrix[i][k] = 1;
                }
            }

            // check if gate output is input to other gates
        }

        /*
        cout << "file open" << endl;

        cout << "number of gates: " << numberGates << endl;

        for (int i = 0 ; i < numberGates; i++)
        {
            cout << netlist.gates[i].name << "  ";
            for (int j = 0; j < numberGates; j++)
                cout <<  netlist.adjMatrix[i][j];
            cout << endl;
        }
        */

        /* TOPO SORT */
        TopoSort top(&netlist);
        top.KahnSort();

        DAG sortedDAG;


        top.sortGates(&sortedDAG);

        QString message = "";

        for (qint16 i =0; i < netlist.getGatesCounter(); i++)
        {
            message  += sortedDAG.gates[i].name + "\t" + QString::number(sortedDAG.gates[i].level) + "\n" ;
        }

        ui->textBrowser_2->setText(message);

    }


}

