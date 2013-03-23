#ifndef OIDINPUTDLG_H
#define OIDINPUTDLG_H

#include <QWidget>
#include <QDialog>

#include <Snmpnet.h>

namespace Ui {
class PswInputDlg;
}
class Ac1608Address;


static QString OldPswStr = "@$%J&$:784ASFGPKY(KW%E$Y%#HWTEHU*57uj5U$^UHW$AweZv><GUIKYT*";

class PswInputDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit PswInputDlg(QWidget *parent = 0);
    ~PswInputDlg();

	bool getNewPsw( Ac1608Address*  oldp);
	//static PswInputDlg *instance();
private slots:    
 
	void okClick();
	void changeClick();
	void cancelClick();

private:
	virtual void	timerEvent ( QTimerEvent * event )override;

	SnmpCallback::RequestStatus setAddressCallback(int status, snmp_session *sp, snmp_pdu *pdu, SnmpObj* so);
	void setAllEnabled( bool flag);
	bool isChangeMode_;
	bool isPasswordChanging_;
	void closeEvent ( QCloseEvent * event );
	//QString id_, oldPsw_, newOid_;
	
	int * oldPsw_, * newPsw_;
	int pswCount_;

	Ac1608Address* currConnAddress_;

    Ui::PswInputDlg *ui;


};

#endif // OIDINPUTDLG_H
