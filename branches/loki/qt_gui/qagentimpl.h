#ifndef QAGENTIMPL_H
#define QAGENTIMPL_H
#include "qagent.h"
#include "KDE/kprocess.h"

#include <qstring.h>

enum
{
	DISPATCH_MAIL,
	DISPATCH_FILE
};

class qagentImpl : public QAgent
{ 
    	Q_OBJECT

public:
    	qagentImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
 	~qagentImpl();

    	void execute ( char *foo );
	void jumpTo ( int pageNo );
	void compileInformation ( void );

	void executeTransport ( void );
			
public slots:
	void pageChanged ( const QString &foo );
	void pathChanged(void);
	void pressedCancel ( void );
	void next ( void );
	void back ( void );
	void help ( void );
	
//FIXME: should this be a protected slot? -- nv.

// Slot for handling calls from KProcess.

	void finishedExecution ( void );

	void GPGfinishedExecution ( void );
	
// Slot for handling received input from the scripts, to move the progress bar

	void receiveData ( KProcess *proc, char *buffer, int buflen );

// Slot for validation of text input for the contact information.

	virtual void dataChanged ( const QString & );
	virtual void launchSaveFileDialog ();
	virtual void dispatchMechanismChanged ( void );
	virtual void sureButtonChanged ( void );
	virtual void gpgBoxChanged ( void );
					
private:
	int dispatchMechanismState;
	int pageOn;
	int totalProgressCounters;
	int progressCounters;	

};

#endif // QAGENTIMPL_H
