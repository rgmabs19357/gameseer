#ifndef WndWnd_H
#define WndWnd_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>
#include <wnd.h>

namespace Ui {
class WndWnd;
}
class WnodeWidget:public QWidget{
	Q_OBJECT
	private slots:

public:
	ResourceID wnode_;

	QTableWidgetItem* id_;

	QTableWidgetItem* x_;
	QTableWidgetItem* y_;
	QTableWidgetItem* w_;
	QTableWidgetItem* h_;
	QTableWidgetItem* ax_;
	QTableWidgetItem* ay_;
	QTableWidgetItem* aw_;
	QTableWidgetItem* ah_;
	Wnd* wnd_;

	WnodeWidget(Wnd* wnd, ResourceID wnode);

	void initTable( QTableWidget* table, int row);
};

class WndWidget:public QWidget{
	Q_OBJECT
	private slots:

public:
	ResourceID inputid_;
	QTableWidgetItem* id_;

	QTableWidgetItem* x_;
	QTableWidgetItem* y_;
	QTableWidgetItem* w_;
	QTableWidgetItem* h_;
	QTableWidgetItem* ax_;
	QTableWidgetItem* ay_;
	QTableWidgetItem* aw_;
	QTableWidgetItem* ah_;
	Wnd* wnd_;

	WndWidget(Wnd* wnd);

	void initTable( QTableWidget* table, int row);
};

class WndWnd : public QWidget
{
    Q_OBJECT
		private slots:
			void currentTabChanged ( int index );
			void	cellClicked ( int row, int column );
public:
    explicit WndWnd(QWidget* parent);
    ~WndWnd();

	private slots:
		//void cellChanged(int,int);
		//void sendClicked(bool);
		//void clearClicked(bool);
private:
	QTableWidget*	wndTable_;
	QTableWidget*	wnodeTable_;


    Ui::WndWnd *ui;


};

#endif // WndWnd_H
