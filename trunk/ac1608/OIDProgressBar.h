#ifndef OIDProgressBar_H
#define OIDProgressBar_H

#include <QWidget>
#include <Snmpnet.h>
#include "qlabel.h"

#include <qlayout.h>
#include <qwt_thermo.h>
#include <qwt_color_map.h>



class OIDProgressBar: public QWidget
{
public:
    OIDProgressBar( Qt::Orientation orientation, QWidget *parent, double value = 0.0 );

    void setValue( double value )
    {
        d_thermo->setValue( value );
    }
	int value(){
		return d_thermo->value();
	}
private:
    QLabel *ql_;
    QwtThermo *d_thermo;


	void * inputDialog_;

	int  val_;
	//volatile int  isRunning_;

	virtual void	mouseReleaseEvent  ( QMouseEvent * event )override;
	void snmpCallback(  SnmpObj*);
public:

	OIDProgressBar( QWidget* w);
	void initSnmp();
	void shutdownSnmp();
};

#endif // OIDProgressBar