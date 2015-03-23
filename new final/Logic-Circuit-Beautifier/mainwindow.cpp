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

    // clear all vectors to start each file processing from scratch

    netlist.adjMatrix.clear();
    netlist.gates.clear();
    netlist.In.clear();
    netlist.InOut.clear();
    netlist.inputs.clear();
    netlist.Out.clear();
    netlist.outputs.clear();
    netlist.Wires.clear();
    netlist.wires.clear();
    netlist.Assign.clear();

    sortedDAG.adjMatrix.clear();
    sortedDAG.gates.clear();
    sortedDAG.In.clear();
    sortedDAG.InOut.clear();
    sortedDAG.inputs.clear();
    sortedDAG.Out.clear();
    sortedDAG.outputs.clear();
    sortedDAG.Wires.clear();
    sortedDAG.wires.clear();
    sortedDAG.Assign.clear();

   // opens file explorer that allows user to select files that are .txt (parsed perl files)
   VerilogFileName = QFileDialog :: getOpenFileName(
                this,
                tr("Choose File"),                              // Dialog Name
                "//",                                           // path starts from root
                "All files (*.txt)"                              // shows only .v files (i.e. Verilog files)
                );

    ui->textBrowser->setText(VerilogFileName);                  // displays path of file in the text browser
    ui->textBrowser_2->clear();
    ui->textBrowser_3->clear();
}

void MainWindow::on_pushButton_clicked()
{
    // RUN
    ui->listWidget->clear();                                // clears display boxes
    ui->textBrowser_3->clear();

    gate * g, * g1;

    unsigned int numberGates;

    if (netlist.readFile(VerilogFileName))                  // opens and reads files
    {                                                       // if successful
        numberGates = netlist.getGatesCounter();            // get counter of gates

        netlist.adjMatrix.resize(numberGates);              // prepares adjacency matrix
        for (qint16 i = 0; i < numberGates; i++)
            netlist.adjMatrix[i].resize(numberGates);

        for (qint16 i = 0; i < numberGates; i++)            // for each gate
        {
            g = &(netlist.gates[i]);                        // gets gate

            for (qint16 j = 0; j < g->inputs.size(); j++)   // for each input of gate
            {
                // check if the each input of the gate is an output of another gate
                int outin = netlist.find(&(netlist.outputs),g->inputs[j]);

                for (qint16 k = 0; k < numberGates; k++)   // for each output
                {
                    g1 = &(netlist.gates[k]);               // get gate
                    if (outin!= -1)
                        if (g1->output == netlist.outputs[outin])   // if gate g and g1 are connected
                            netlist.adjMatrix[i][k] = 1;    // creates link in adjMatrix to indicate connection
                }
            }
        }

        /* TOPO SORT */
        TopoSort top(&netlist);         // instantiates topoSort of the DAG
        top.KahnSort();                 // applies Kahn Sort
        top.sortGates(&sortedDAG);      // gets sorted gates

        // display levels in levels list window
        ui->listWidget->addItem( "Level 0 ");
        for (qint16 i = 1; i <= sortedDAG.gates[netlist.getGatesCounter()-1].level ; i++)
        {
            ui->listWidget->addItem("Level " + QString::number(i) );
        }
        ui->listWidget->addItem("Level " + QString::number(sortedDAG.gates[netlist.getGatesCounter()-1].level + 1) );

        /*
        // display assign statements
        QString message = "";
        for (qint16 i = 0; i < sortedDAG.gates[netlist.getGatesCounter()-1].level ; i++)
        {
            message += netlist.Assign[i].first + ",\t " + netlist.Assign[i].second + "\n";
        }
        */

       //ui->textBrowser_2->setText( netlist.Assign[0].first + ",\t " + netlist.Assign[0].second + "\n");
    }
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    // upon selection of level, displays the gates in the level

    QString message = "";

    qint16 index = ui->listWidget->currentRow();                    // gets index of selected row

    if (index == 0)                                                 // if index == 0, display inputs
    {
        message += "--Inputs-- \n";

        for (qint16 i =0; i < netlist.In.size(); i++)
        {
            message += netlist.In[i] + "\n";
        }
    }
    else                                                            // if index == last level, display outputs
        if (index == sortedDAG.gates[netlist.getGatesCounter()-1].level + 1)
        {
            message += "--Outputs-- \n";

            for (qint16 i =0; i < netlist.Out.size(); i++)
            {
                message += netlist.Out[i] + "\n";
            }
        }
        else                                                    // else display gates per level
            for (qint16 i =0; i < netlist.getGatesCounter(); i++)
            {
                if (sortedDAG.gates[i].level == index)
                    message  += sortedDAG.gates[i].name + "\n" ;
            }

    ui->textBrowser_3->setText(message);

}

