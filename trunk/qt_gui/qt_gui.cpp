#include "qt_gui.h"
#include "host_def.h"
#include "utils.h"
#include "qagent_globals.h"
#include "qagentimpl.h"

#include <qpushbutton.h>

#include <qapplication.h>

void run_QT_GUI ( int argc, char *argv[] )
{
	QApplication app(argc,argv);
	QTranslator translator(&app);
	translator.load("qagent_en.qm");	// fixme
	app.installTranslator(&translator);

	qagentImpl *impl = new qagentImpl;

	app.setMainWidget(impl);

	impl->show();
	
	app.exec();
}

QPixmap loadPixmap ( void )
{
	static int active=FALSE;
	static QPixmap pixmap;
	if (active==FALSE)
	{
		pixmap.load(QString::fromLatin1(work_dir)
			+QString::fromLatin1("/")
			+QString::fromLatin1(_GEN_HOSTDEF_SIDEBAR_PIXMAP));
		active=TRUE;
	}
	return pixmap;
}

