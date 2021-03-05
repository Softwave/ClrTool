#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QColorDialog>
#include <QContextMenuEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include <QFontDatabase>
#include <QList>
#include <QPair>
#include <QAbstractItemView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_btnNewColor_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void ProvideContextMenu(const QPoint &);

    void on_BtnLoad_clicked();

    void on_BtnSave_clicked();

    void saveToFile();
    void loadFromFile();
    void updateInterface();

    void on_pushButton_2_clicked();

    void on_listWidget_indexesMoved(const QModelIndexList &indexes);


    void on_listWidget_itemEntered(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QMap<int, QString> ourColors;
    int currentRow;
    QString currentName;
    bool eventFilter(QObject *watched, QEvent *event);
    void reorderList();
};
#endif // MAINWINDOW_H
