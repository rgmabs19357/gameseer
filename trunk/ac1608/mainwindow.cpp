#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include "inputGainCtrlWnd.h"
#include "CopyParamWnd.h"
#include "DevicesWnd.h"
#include "GateNOMWnd.h"
#include "HighPassWnd.h"
#include "Level8CHWnd.h"
#include "MatrixMixerWnd.h"
#include "MetersWnd.h"
#include "PresetWnd.h"
#include "homepage.h"
#include "peqwnd.h"
#include "nomwnd.h"
#include <QAction.h>
#include <QLineEdit.h>
#include <QTabWidget.h>
#include <CobraNetWnd.h>
#include "SnmpNetWnd.h"

#include "snmpnet.h"
#include "configmgr.h"
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include <functional>

#include <QTableView>


using namespace std::placeholders;

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,inputGainCtrlWnd_(new InputGainCtrlWnd)
    ,gateNOMWnd_(new GateNOMWnd)
    ,highPassWnd_(new HighPassWnd)
	,deviceswnd_(new DevicesWnd)
	,homepage_(new HomePage)
	,matrixMixerWnd_(new MatrixMixerWnd)
	,peqWnd_(new PEQWnd)
	,nomWnd_(new NOMWnd)
	,presetWnd_(new PresetWnd)
	,cobraNetWnd_(new CobraNetWnd)
	,snmpNetWnd_(new SnmpNetWnd)

{
    ui->setupUi(this);

	_tab = findChild<QTabWidget*>( "tabWidget");

	
	_tab->addTab(homepage_, "Homepage" );
	_tab->addTab(deviceswnd_, "Devices" );
	_tab->addTab(inputGainCtrlWnd_, "Input" );
	_tab->addTab(gateNOMWnd_, "Gate" );
	_tab->addTab(highPassWnd_, "HighPass" );
	_tab->addTab(peqWnd_, "PEQ" );
	_tab->addTab(matrixMixerWnd_, "MatrixMixer" );
	_tab->addTab(nomWnd_, "NOM" );
	_tab->addTab(presetWnd_, "Preset" );
	_tab->addTab(cobraNetWnd_, "CobraNet" );
	_tab->addTab(snmpNetWnd_, "SnmpNet" );
	
	deviceswnd_->initAddresses();

	connect( _tab, SIGNAL(currentChanged (int)), this, SLOT(tabChanged(int)));

    connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionChangePsw_clicked(QAction*)));
    connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionCopyParam_clicked(QAction*)));
	connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionEdit_clicked(QAction*)));
}


void MainWindow::tabChanged (int index){
	QWidget* currWidget = _tab->widget( index);
	if ( currWidget == deviceswnd_){
	}
}
MainWindow::~MainWindow()
{
    delete ui;
    delete inputGainCtrlWnd_;
    delete gateNOMWnd_;
    delete highPassWnd_;

	delete deviceswnd_;
	delete homepage_;
	delete matrixMixerWnd_;
	delete peqWnd_;
	delete nomWnd_;
	delete presetWnd_;
	delete cobraNetWnd_;
	delete snmpNetWnd_;
}

void MainWindow::on_inputGainControl_clicked()
{
    if ( inputGainCtrlWnd_->isVisible()){
        inputGainCtrlWnd_->hide();
    }else{
        inputGainCtrlWnd_->show();
    }
}

void MainWindow::on_highPass_clicked(){
    if ( highPassWnd_->isVisible()){
        highPassWnd_->hide();
    }else{
        highPassWnd_->show();
    }

}


void MainWindow::on_gateNom_clicked()
{

    if ( gateNOMWnd_->isVisible()){
        gateNOMWnd_->hide();
    }else{
        gateNOMWnd_->show();
    }
}

void MainWindow::on_actionChangePsw_clicked( QAction* action){
    if (action->objectName() != "actionChangePsw" ) return;

}

void MainWindow::closeEvent(QCloseEvent * ){
    QCoreApplication::exit();
}
void MainWindow::resizeEvent(QResizeEvent * event){

	_tab->setGeometry( 0, 0, this->width()+2, this->height()-40);

	QTableWidget* t = _tab->findChild<QTableWidget* >("tableDevices");
	if (t){
	t->setGeometry( 0, 0, this->width()+2, this->height()-40);
	t->setColumnWidth( 0, 150);
	t->setColumnWidth( 2, 100);
	t->setColumnWidth( 3, 100);
	t->setColumnWidth( 4, 100);
	t->setColumnWidth( 5, 100);
	t->setColumnWidth( 1, (int)(t->width() - 600) );
	}

	t = _tab->findChild<QTableWidget* >("tableOids");
	if (t){
		t->setGeometry( 0, 0, this->width()+2, this->height()-40);
	t->setColumnWidth( 0, 150);
	t->setColumnWidth( 2, 100);
	t->setColumnWidth( 3, 100);
	t->setColumnWidth( 4, 100);
	t->setColumnWidth( 5, 100);
	t->setColumnWidth( 1, (int)(t->width() - 600) );
	}


}

//SnmpCallback::RequestStatus dispatchFunc(int status, snmp_session *sp, snmp_pdu *pdu, SnmpObj* so){
//	//netsnmp_variable_list *vars;
//	//for (vars = pdu->variables; vars; vars = vars->next_variable){
//	//print_variable(pdu->variables->name, pdu->variables->name_length, vars);
//	const int len = 1024;
//	char buf[len];
//	memset( buf, 0, 1024);
//	snprint_variable( buf, len, pdu->variables->name, pdu->variables->name_length, pdu->variables);
//	qDebug()<<buf;
//
//	//}
//	return SnmpCallback::RequestAgain;
//}

void MainWindow::on_actionCopyParam_clicked(QAction* action){
	if (action->objectName() != "action_copy_param" ) return;
    //sn.snmpmain();
	//SnmpNet::instance()->walk("1.3.6.1.4.1.2680.1.1.3");
	//SnmpNet::instance()->get(".1.3.6.1.4.1.2680.1.1.3.4.0");
	//SnmpNet::instance()->addAsyncGet(".1.3.6.1.4.1.2680.1.1.3.4.0", "192.168.1.100", "public", std::bind<SnmpCallbackFunc>( dispatchFunc, _1, _2, _3, _4));
	//SnmpNet::instance()->addAsyncGet(".1.3.6.1.4.1.2680.1.4.2.1.59.26.36.46.3.2.1.2.4", "192.168.1.100", "public",  std::bind<SnmpCallbackFunc>( dispatchFunc, _1, _2, _3, _4));

	//SnmpNet::instance()->addAsyncGet(".1.3.6.1.2.1.1.3.0", "192.168.1.100", "public",  std::bind<SnmpCallbackFunc >( dispatchFunc, _1, _2, _3, _4));
	//SnmpNet::instance()->listenAddress( "192.168.1.100", std::bind<SnmpCallbackFunc >( dispatchFunc, _1, _2, _3, _4));
	//ConfigMgr::instance();
}
void MainWindow::on_actionEdit_clicked(QAction* action){
	if (action->objectName() != "action_mode_edit" ) return;
	if (action->isChecked()) {
		ConfigMgr::instance()->setOidEditable(true) ;
	}else{
		ConfigMgr::instance()->setOidEditable(false) ;
	}

	
}