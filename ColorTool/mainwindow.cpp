#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->setDragEnabled(true);
    ui->listWidget->viewport()->setAcceptDrops(true);
    ui->listWidget->setDropIndicatorShown(true);
    ui->listWidget->setDragDropMode(QAbstractItemView::InternalMove);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ProvideContextMenu(const QPoint &)));

    this->setFixedSize(QSize(390, 644));

    QFontDatabase::addApplicationFont(":/fonts/TerminalVector.ttf");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    item->setBackgroundColor(item->text());
}

void MainWindow::on_btnNewColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    currentName = (QString)color.name();
    ui->listWidget->addItem(currentName);
    currentRow = ui->listWidget->count()-1;

    QListWidgetItem* tempItem = ui->listWidget->item(currentRow);
    tempItem->setBackgroundColor(tempItem->text());
    tempItem->setFont(QFont("TerminalVector", 9));
    tempItem->setFlags(tempItem->flags()
                       .setFlag(Qt::ItemIsEditable, false));

    ourColors.insert(currentRow, currentName);

}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    item->setBackgroundColor(color);
    item->setText(color.name());
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

}

void MainWindow::ProvideContextMenu(const QPoint &pos)
{
    QPoint item = ui->listWidget->mapToGlobal(pos);
    QMenu submenu;
    submenu.addAction("Delete");
    QAction* rightClickItem = submenu.exec(item);
    if (rightClickItem && rightClickItem->text().contains("Delete"))
    {
        ui->listWidget->takeItem(ui->listWidget->indexAt(pos).row());
        ourColors.take(ui->listWidget->indexAt(pos).row());
    }

}

void MainWindow::on_BtnLoad_clicked()
{
    loadFromFile();
}

void MainWindow::on_BtnSave_clicked()
{
    saveToFile();
}

void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Colors"), "",
                                                    tr("Save Colors (*.clrs);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("?Unable to open file"),
                                     file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_0);
        out << ourColors;
    }
}

void MainWindow::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Colors File"), "",
            tr("Address Book (*.clrs);;All Files (*)"));


        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly))
            return;

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);


        ourColors.clear();   // clear our colors
        ui->listWidget->clear();

        in >> ourColors;


       QMap<int, QString>::iterator i;
       for (i = ourColors.begin(); i != ourColors.end(); i++)
       {
           currentRow = i.key();
           currentName = i.value();
           updateInterface();
       }



}

void MainWindow::updateInterface()
{
        ui->listWidget->addItem(currentName);
        QListWidgetItem* tempItem = ui->listWidget->item(ui->listWidget->count()-1);
        tempItem->setBackgroundColor(tempItem->text());
        tempItem->setFont(QFont("TerminalVector", 9));
        tempItem->setFlags(tempItem->flags()
                       .setFlag(Qt::ItemIsEditable, false));
}


void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("ColorTool; keep track of your colors!");
    msgBox.setInformativeText("By Jessica Leyba, 2021, GPL v3, see license for more information");
    msgBox.exec();
}
