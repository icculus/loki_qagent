#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "qagentimpl.h"
#include "utils.h"
#include "qt_gui.h"
#include "qagent_globals.h"

#include "host_def.h"
#include "KDE/kprocess.h"

#include <qcombobox.h>
#include <qcheckbox.h>
#include <qfiledialog.h>
#include <qwizard.h>
#include <qradiobutton.h>
#include <qpushbutton.h>
#include <qmultilineedit.h>
#include <qtextview.h>
#include <qlineedit.h>
#include <qprogressbar.h>
#include <qlabel.h>
#include <qobject.h>

#include <sys/types.h>	// pid_t

#ifdef ENABLE_SETUPDB
#include "../../setupdb/setupdb.h"
#endif

#include "getline.h"

/* 
 *  Constructs a qagentImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The wizard will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal wizard.
 */

qagentImpl::qagentImpl( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QAgent( parent, name, modal, fl )
{
	pageOn = QAGENT_INTRO_PAGE;

// Set the caption..

	setCaption(QObject::tr(_GEN_HOSTDEF_PROGRAM_NAME));

	dispatchMechanismState = DISPATCH_MAIL;

//FIXME: This shouldn't be hard coded if we can help it. -- nv.

	totalProgressCounters = 14;
	progressCounters = 0;

	scanProgressBar->setTotalSteps(totalProgressCounters);
	scanProgressBar->setProgress(0); // otherwise we segfault...

	introTextLabel->setText(QObject::tr("intro_text"));
	scanningTextLabel->setText(QObject::tr("scan_text"));
	describeFindingsLabel->setText(QObject::tr("findings_text"));
	userCommentLabel->setText(QObject::tr("usercomment_text"));	
	dispatchMechanismLabel->setText(QObject::tr("dispatch_mechanism_text"));
	contactInfoLabel->setText(QObject::tr("contact_info_text"));
	finalCheckLabel->setText(QObject::tr("final_check_text"));
	dumpFileEdit->setText(QString::QString(home)+QString::fromLatin1("/qagent.txt"));

	FILE *fp = fopen((QString::fromLatin1(work_dir)+QString::fromLatin1("/privacy.txt")),"rt");
	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, fp) >= 0)
	{
		line[strlen(line)-1] = 0;	// strip newline character.
		privacyPolicyEdit->insertLine(QString::QString(line));
	}
	fclose(fp);
	
	connect(this, SIGNAL(selected (const QString &)),
		this, SLOT(pageChanged(const QString &)));

	connect(this->cancelButton(), SIGNAL(clicked()),
		this, SLOT(pressedCancel()));

	connect(this->finishButton(), SIGNAL(clicked()),
		this, SLOT(pressedCancel()));

	QWidget *temp_page = page( QAGENT_INTRO_PAGE );
	setHelpEnabled( temp_page, FALSE );
	
	temp_page = page( QAGENT_PATH_PAGE );
	setHelpEnabled( temp_page, FALSE );
	temp_page = page( QAGENT_PRODUCT_PAGE );
	setHelpEnabled( temp_page, FALSE );

	temp_page = page( QAGENT_SCAN_PAGE );
	setHelpEnabled( temp_page, FALSE );

	setBackEnabled( temp_page, FALSE );
	setNextEnabled( temp_page, FALSE );
	temp_page = page( QAGENT_FINDINGS_PAGE );
	setHelpEnabled( temp_page, FALSE );
	setBackEnabled( temp_page, FALSE );
	temp_page = page( QAGENT_COMMENT_PAGE );
	setHelpEnabled( temp_page, FALSE );
	temp_page = page( QAGENT_CONTACT_PAGE );
	setHelpEnabled( temp_page, FALSE );
	setNextEnabled( temp_page, FALSE );
	temp_page = page( QAGENT_DISPATCH_PAGE );
	setHelpEnabled( temp_page, FALSE );
	temp_page = page( QAGENT_FENRIS_PAGE );
	setHelpEnabled( temp_page, FALSE );
	temp_page= page(QAGENT_POLICY_PAGE);
	setHelpEnabled(temp_page, FALSE);
	temp_page = page( QAGENT_NOGPG_PAGE );
	setHelpEnabled( temp_page, FALSE );
	temp_page = page( QAGENT_FILE_PAGE );
	setHelpEnabled( temp_page, FALSE );
	temp_page = page( QAGENT_FINAL_CHECK_PAGE );
	setNextEnabled ( temp_page, FALSE );
	setHelpEnabled ( temp_page, FALSE );
	temp_page = page( QAGENT_FINISHED_PAGE );
	setFinishEnabled ( temp_page, TRUE );
	setHelpEnabled ( temp_page, FALSE );
	setBackEnabled ( temp_page, FALSE );

// FIXME: check if the user currently has a product selected

#ifdef ENABLE_SETUPDB
	const char *foo;
	for (foo = loki_getfirstproduct(); foo; foo = loki_getnextproduct())
	{
		productComboBox->insertItem(foo);
	}
#endif

}

/*  
 *  Destroys the object and frees any allocated resources
 */

qagentImpl::~qagentImpl()
{
    // no need to delete child widgets, Qt does it all for us
}

void qagentImpl::pathChanged ( void )
{
#ifdef VERBOSE
	printf("Path changed\n");
#endif

	if (standardPathButton->isChecked())
	{
		mode = QAGENT_STANDARD_MODE;
	}
	else if (standardPathButton->isChecked())
	{
		mode = QAGENT_ADVANCED_MODE;
	}
	else
	{
		mode = QAGENT_STANDARD_MODE;
	}

}
void qagentImpl::pageChanged ( const QString &name )
{
#ifdef VERBOSE
	printf("page changed\n");
#endif
}

void qagentImpl::jumpTo ( int pageNo )
{

// This assumes that pageOn represents the current page accurately, which
// should always be the case.

	int i;

	if (pageOn < pageNo)
	{
		for (i = pageOn; i < pageNo; i++)
		{
			QWizard::next();
		}
	}
	else if (pageOn == pageNo)
	{
		// DO NOTHING
	}
	else if (pageOn > pageNo)
	{
		for (i = pageOn; i > pageNo; i--)
		{
			QWizard::back();
		}
	}
	pageOn = pageNo;
}

void qagentImpl::back ( void )
{

#ifdef VERBOSE
	printf("pressed back\n");
#endif

//	QWizard::back();

	if (pageOn == QAGENT_NOGPG_PAGE)
	{
		jumpTo(QAGENT_DISPATCH_PAGE);
	}
	else if (pageOn == QAGENT_POLICY_PAGE)
	{

		if (dumpDispatchButton->isChecked())
		{
			jumpTo(QAGENT_FILE_PAGE);
		}
		else
		{
			jumpTo(QAGENT_DISPATCH_PAGE);
		}
	}
	else
	{
		pageOn--;
		QWizard::back();
	}

#ifdef VERBOSE
	printf("pageOn: %i\n",pageOn);
#endif

}

void qagentImpl::next ( void )
{

#ifdef VERBOSE
	printf("pressed next\n");
#endif

//PAGES REQUIRING JUMP CHANGES SHOULD BE PUT HERE.

	if ((pageOn == QAGENT_DISPATCH_PAGE) && (emailDispatchButton->isChecked()))
	{
		if (check_for_GPG() == FALSE)
		{
			jumpTo(QAGENT_NOGPG_PAGE);
		}
		else
		{
			jumpTo(QAGENT_POLICY_PAGE);
		}
	}
	else if ((pageOn == QAGENT_FILE_PAGE) && (dumpDispatchButton->isChecked()))
	{
		if (check_for_GPG() == FALSE)
		{
			jumpTo(QAGENT_NOGPG_PAGE);
		}
		else
		{
			jumpTo(QAGENT_POLICY_PAGE);
		}
	}
	else
	{

// PAGES REQUIRING ACTIONS UPON CONNECTION SHOULD BE PUT HERE.

		pageOn++;
		QWizard::next();

// if we don't have SetupDB support enabled, don't show the product page
		if (pageOn == QAGENT_PRODUCT_PAGE)
		{
#ifndef ENABLE_SETUPDB
			jumpTo(QAGENT_SCAN_PAGE)
#endif
		}
	
		else if (pageOn == QAGENT_SCAN_PAGE)
		{
			execute("qagent.sh");
		}
		else if (pageOn == QAGENT_FINDINGS_PAGE)
		{
			FILE *fp = fopen(dump_path,"rt");
			char *line = NULL;
			size_t len = 0;
			while (getline(&line, &len, fp) >= 0)
			{
				line[strlen(line)-1] = 0;	// strip newline

findingsBox->insertLine(QString::QString(line));
			}
			fclose(fp);
		}
	
	
	}		
	
#ifdef VERBOSE
	printf("pageOn: %i\n",pageOn);
#endif
	
}	
	
void qagentImpl::execute (char *foo)
{

	KShellProcess *proc = new KShellProcess;
	*proc << QString::fromLatin1("/bin/sh")
	<< (QString::fromLatin1(work_dir)+QString::fromLatin1("/")+QString::fromLatin1(foo))
	<< QString::fromLatin1("--support_path")
	<< QString::fromLatin1(support_path)
	<< QString::fromLatin1("--dump_path")
	<< QString::fromLatin1(dump_path);

// export parameters.

	if ( product_cdrom )
	{
		*proc 	<< QString::fromLatin1("--product_cdrom") 
			<< QString::fromLatin1(product_cdrom);
	}

	if ( product_name )
	{
		*proc 	<< QString::fromLatin1("--product_name") 
			<< QString::fromLatin1(product_name);
	}

	if ( product_path )
	{
		*proc 	<< QString::fromLatin1("--product_path") 
			<< QString::fromLatin1(product_path);
	}

	if ( product_desc )
	{
		*proc 	<< QString::fromLatin1("--product_desc") 
			<< (QString::fromLatin1("\"")+QString::fromLatin1(product_desc)+QString::fromLatin1("\""));
	}

	if ( product_version )
	{
		*proc 	<< QString::fromLatin1("--product_version") 
			<< QString::fromLatin1(product_version);
	}

	if ( product_prefs )
	{
		*proc 	<< QString::fromLatin1("--product_prefs") 
			<< QString::fromLatin1(product_prefs);
	}

	if ( stack_trace_path )
	{
		*proc 	<< QString::fromLatin1("--product_stack")
			<< QString::fromLatin1(stack_trace_path);
	}

	QObject::connect(proc, SIGNAL(processExited(KProcess *)),
			this, SLOT(finishedExecution()));
	QObject::connect(proc, SIGNAL(receivedStdout(KProcess *, char *, int)),
			this, SLOT(receiveData(KProcess *, char *, int)));

	proc->start(KShellProcess::NotifyOnExit, KShellProcess::All);


}

void qagentImpl::pressedCancel ( void )
{
// for some reason, this isn't registering as the last window being closed.
// so we have to do it manually.

#ifdef VERBOSE
	printf("pressed cancel/Finish\n");
#endif
	close();
}

void qagentImpl::help ( void )
{
#ifdef VERBOSE
	printf("pressed help\n");
#endif
}

void qagentImpl::finishedExecution ( void )
{
#ifdef VERBOSE
	printf("WE FINISHED EXECUTION!\n");
#endif
	scanProgressBar->setProgress(totalProgressCounters);
	setNextEnabled (page(QAGENT_SCAN_PAGE), TRUE);
}

void qagentImpl::receiveData ( KProcess *proc, char *buffer, int buflen )
{
	char *foo = (char *)malloc(buflen);	// swap NULL for \n
	strncpy(foo,buffer,buflen-1);
	foo[buflen-1] = 0;

	if (strcmp(foo, "<r>") == 0)
	{
		progressCounters++;
		scanProgressBar->setProgress(progressCounters);
	}
	else if (strncmp(foo, "<e>",3) == 0)
	{
// oh-oh, we hit an error. 
		printf("Error: %s\n", foo+3);	// print it to the console for now.
	}

	free(foo);

}

void qagentImpl::dataChanged ( const QString & )
{
	if (
		!fullNameEdit->text().isEmpty() &&
		!emailAddressEdit->text().isEmpty())
	{
		setNextEnabled ( page(QAGENT_CONTACT_PAGE), TRUE );		
	}
	else
	{
		setNextEnabled ( page(QAGENT_CONTACT_PAGE), FALSE );
	}

}

void qagentImpl::launchSaveFileDialog ( void )
{
	QString fn = QFileDialog::getSaveFileName ( dumpFileEdit->text(), QString::null );
	dumpFileEdit->setText(fn);
}

void qagentImpl::dispatchMechanismChanged ( void )
{
	if (emailDispatchButton->isChecked())
	{
#ifdef VERBOSE
		printf("Dispatch Mechanism: MAIL\n");
#endif
		dispatchMechanismState = DISPATCH_MAIL;
	}
	else if (dumpDispatchButton->isChecked())
	{
#ifdef VERBOSE
		printf("Dispatch Mechanism: File Dump\n");
#endif
		dispatchMechanismState = DISPATCH_FILE;
	}
	else
	{
		printf("UNKNOWN DISPATCH MECHANISM CHOSEN!\n");
	}
}

void qagentImpl::compileInformation ( void )
{
	if (user_name != NULL)
	{
		free(user_name);
		user_name = NULL;
	}

	if (user_email != NULL)
	{
		free(user_email);
		user_email = NULL;
	}

	if (user_regno != NULL)
	{
		free(user_regno);
		user_regno = NULL;
	}

	if (user_comment != NULL)
	{
		free(user_comment);
		user_comment = NULL;
	}

	user_name = (char *)malloc(strlen(fullNameEdit->text())+1);
	strcpy(user_name,fullNameEdit->text());

	user_email = (char *)malloc(strlen(emailAddressEdit->text())+1);
	strcpy(user_email,emailAddressEdit->text());

	if (!registrationNumberEdit->text().isEmpty())
	{
		user_regno = (char *)malloc(strlen(registrationNumberEdit->text())+1);
		strcpy(user_regno,registrationNumberEdit->text());
	}

	if (!userCommentBox->text().isEmpty())
	{
		user_comment = (char *)malloc(strlen(userCommentBox->text())+1);
		strcpy(user_comment,userCommentBox->text());
	}


}

void qagentImpl::sureButtonChanged ( void )
{
	if (sureCheckBox->isChecked())
	{
		setNextEnabled(page(QAGENT_FINAL_CHECK_PAGE),TRUE);
	}
	else
	{
		setNextEnabled(page(QAGENT_FINAL_CHECK_PAGE), FALSE);
	}
}

void qagentImpl::gpgBoxChanged ( void )
{
	if (gpgCheckBox->isChecked())
	{
		useGPG = TRUE;
	}
	else
	{
		useGPG = FALSE;
	}
}

void qagentImpl::executeTransport ( void )
{

	if (useGPG)

	{
		
		encrypt_path = (char *)malloc(strlen(support_path)+strlen(ENCRYPT_FILE)+1);
		strcpy(encrypt_path,support_path);
		strcat(encrypt_path,ENCRYPT_FILE);

		KShellProcess *proc = new KShellProcess;
		*proc << QString::fromLatin1("/bin/sh")
		<< (QString::fromLatin1(work_dir)+QString::fromLatin1("/encrypt_gpg.sh"))
		<< QString::fromLatin1(dump_path)
		<< QString::fromLatin1(encrypt_path)
		<< (QString::fromLatin1(work_dir)+QString::fromLatin1("/")+QString::fromLatin1(_GEN_HOSTDEF_KEY_FILE));
		
// What a mess.

		QObject::connect(proc, SIGNAL(processExited(KProcess *)),
			this, SLOT(GPGfinishedExecution()));
		
		proc->start(KShellProcess::NotifyOnExit, KShellProcess::NoCommunication);

	}
	else
	{
		GPGfinishedExecution();
	}
			
}

void qagentImpl::GPGfinishedExecution ( void )
{

// FIXME this should be moved into utils.cpp!!!

// FIRST: Assemble the dump file.

	FILE *read, *write;
	char *target_path;

	target_path = (char *)malloc(strlen(support_path)+strlen(TARGET_FILE)+1);
	strcpy(target_path, support_path);
	strcat(target_path, TARGET_FILE);

	write = fopen(target_path,"wt");
	read = fopen(header_path,"rt");
	
	char *line = NULL;
	size_t len = 0;
	
	while (getline(&line, &len, read) >= 0)
	{
		fprintf(write,line);
	}

	fclose(read);

	if (useGPG)
	{
		read = fopen(encrypt_path,"rt");
	}
	else
	{
		read = fopen(dump_path,"rt");
	}
	
	while (getline(&line, &len, read) >= 0)
	{
		fprintf(write, line);
	}

	fclose(read);

	fclose(write);

	
// SECOND: Check the dispatch mechanism.

	if (dispatchMechanismState == DISPATCH_FILE)
	{
		KShellProcess *proc = new KShellProcess;
		*proc 	<< QString::fromLatin1("/bin/sh")
		      	<< (QString::fromLatin1(work_dir)+QString::fromLatin1("/transport_file.sh"))
			<< QString::fromLatin1(target_path)
			<< dumpFileEdit->text();
		proc->start(KShellProcess::DontCare, KShellProcess::NoCommunication);
		
	}
	else
	{
		KShellProcess *proc = new KShellProcess;
		*proc 	<< QString::fromLatin1("/bin/sh")
			<< (QString::fromLatin1(work_dir)+QString::fromLatin1("/transport_mail.sh"))
			<< QString::fromLatin1(target_path)
			<< QString::fromLatin1(user_email);
		proc->start(KShellProcess::DontCare, KShellProcess::NoCommunication);
	}
	
}
