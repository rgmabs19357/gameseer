#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DevicesWnd;
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

		
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:

		void tabChanged (int);

    private:

		QTabWidget* _tab;

        Ui::MainWindow *ui;

        DevicesWnd *devicesWnd_;

		//SnmpNetWnd * snmpNetWnd_;

        void closeEvent(QCloseEvent * event);
		void resizeEvent(QResizeEvent * event);

};

#endif // MAINWINDOW_H
