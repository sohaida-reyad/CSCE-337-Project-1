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
DAG netlist;
DAG sortedDAG;

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

   // clear
    netlist.adjMatrix.clear();
    netlist.gates.clear();
    netlist.In.clear();
    netlist.InOut.clear();
    netlist.inputs.clear();
    netlist.Out.clear();
    netlist.outputs.clear();
    netlist.Wires.clear();
    netlist.wires.clear();

    sortedDAG.adjMatrix.clear();
    sortedDAG.gates.clear();
    sortedDAG.In.clear();
    sortedDAG.InOut.clear();
    sortedDAG.inputs.clear();
    sortedDAG.Out.clear();
    sortedDAG.outputs.clear();
    sortedDAG.Wires.clear();
    sortedDAG.wires.clear();

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
    // RUN
    ui->listWidget->clear();
    ui->textBrowser_3->clear();

    gate * g, * g1;

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

        /* TOPO SORT */
        TopoSort top(&netlist);
        top.KahnSort();
        top.sortGates(&sortedDAG);

        ui->listWidget->addItem( "Level 0 ");
        for (qint16 i = 1; i <= sortedDAG.gates[netlist.getGatesCounter()-1].level ; i++)
        {
            ui->listWidget->addItem("Level " + QString::number(i) );
        }
        ui->listWidget->addItem("Level " + QString::number(sortedDAG.gates[netlist.getGatesCounter()-1].level + 1) );

        QString message = "";
        for (qint16 i = 1; i <= sortedDAG.gates[netlist.getGatesCounter()-1].level ; i++)
        {
            message += netlist.Assign[i].first + ",\t " + netlist.Assign[i].second + "\n";
        }
        ui->textBrowser_2->setText(message);
    }


}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString message = "";

    qint16 index = ui->listWidget->currentRow();

    if (index == 0)
    {
        message += "--Inputs-- \n";

        for (qint16 i =0; i < netlist.In.size(); i++)
        {
            message += netlist.In[i] + "\n";
        }
    }
    else
        if (index == sortedDAG.gates[netlist.getGatesCounter()-1].level + 1)
        {
            message += "--Outputs-- \n";

            for (qint16 i =0; i < netlist.Out.size(); i++)
            {
                message += netlist.Out[i] + "\n";
            }
        }
        else
            for (qint16 i =0; i < netlist.getGatesCounter(); i++)
            {
                if (sortedDAG.gates[i].level == index)
                    message  += sortedDAG.gates[i].name + "\n" ;
            }

    ui->textBrowser_3->setText(message);

}

