/****************************************************************************
** Form interface generated from reading ui file 'qagent.ui'
**
** Created: Fri Nov 3 01:48:36 2000
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef QAGENT_H
#define QAGENT_H

#include <qvariant.h>
#include <qwizard.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QButtonGroup;
class QCheckBox;
class QComboBox;
class QFrame;
class QLabel;
class QLineEdit;
class QMultiLineEdit;
class QProgressBar;
class QPushButton;
class QRadioButton;
class QWidget;

class QAgent : public QWizard
{ 
    Q_OBJECT

public:
    QAgent( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~QAgent();

    QWidget* Widget2;
    QLabel* PixmapLabel1;
    QLabel* introTextLabel;
    QWidget* Widget13;
    QLabel* PixmapLabel1_2_2_2_2_2_2_2_2_2_2_3;
    QLabel* TextLabel1_2;
    QButtonGroup* ButtonGroup2;
    QRadioButton* standardPathButton;
    QLabel* TextLabel2_2;
    QRadioButton* advancedPathButton;
    QLabel* TextLabel3;
    QLabel* TextLabel4;
    QWidget* Widget12;
    QLabel* PixmapLabel1_2_2_2_2_2_2_2_2_2_2_2;
    QComboBox* productComboBox;
    QLabel* TextLabel1;
    QWidget* Widget3;
    QLabel* PixmapLabel1_2;
    QProgressBar* scanProgressBar;
    QLabel* scanningTextLabel;
    QWidget* Widget4;
    QLabel* PixmapLabel1_2_2;
    QLabel* describeFindingsLabel;
    QMultiLineEdit* findingsBox;
    QWidget* Widget5;
    QLabel* PixmapLabel1_2_2_2;
    QLabel* userCommentLabel;
    QMultiLineEdit* userCommentBox;
    QWidget* Widget7;
    QLabel* PixmapLabel1_2_2_2_2_2;
    QLineEdit* fullNameEdit;
    QLabel* emailAddressLabel;
    QLineEdit* emailAddressEdit;
    QLabel* regNoLabel;
    QLineEdit* registrationNumberEdit;
    QLabel* fullNameLabel;
    QLabel* contactInfoLabel;
    QWidget* Widget14;
    QLabel* PixmapLabel1_2_2_2_2_2_2_2_2_2_2_3_2;
    QLabel* TextLabel11;
    QFrame* Frame3;
    QLabel* TextLabel12;
    QLineEdit* LineEdit15;
    QLabel* TextLabel13;
    QLineEdit* LineEdit16;
    QLabel* TextLabel14;
    QMultiLineEdit* MultiLineEdit11;
    QLabel* TextLabel15;
    QCheckBox* CheckBox9;
    QWidget* Widget6;
    QCheckBox* gpgCheckBox;
    QLabel* PixmapLabel1_2_2_2_2;
    QLabel* dispatchMechanismLabel;
    QButtonGroup* ButtonGroup1;
    QRadioButton* emailDispatchButton;
    QRadioButton* dumpDispatchButton;
    QWidget* Widget9;
    QLabel* PixmapLabel1_2_2_2_2_2_2_2;
    QLineEdit* dumpFileEdit;
    QLabel* dumpFileLabel;
    QPushButton* chooseFileButton;
    QWidget* Widget8;
    QLabel* PixmapLabel1_2_2_2_2_2_2;
    QLabel* TextLabel8;
    QWidget* Widget12_2;
    QLabel* PixmapLabel1_2_2_2_2_2_2_2_2;
    QLabel* privacyLabel;
    QMultiLineEdit* privacyPolicyEdit;
    QWidget* Widget10;
    QMultiLineEdit* finalCheckEdit;
    QCheckBox* sureCheckBox;
    QLabel* finalCheckLabel;
    QLabel* PixmapLabel1_2_2_2_2_2_2_2_2_2;
    QWidget* Widget11;
    QLabel* PixmapLabel1_2_2_2_2_2_2_2_2_2_2;
    QLabel* TextLabel2;

public slots:
    virtual void dataChanged(const QString &);
    virtual void dispatchMechanismChanged();
    virtual void gpgBoxChanged();
    virtual void launchSaveFileDialog();
    virtual void pathChanged();
    virtual void sureButtonChanged();

protected:
    QVBoxLayout* vbox;
    QVBoxLayout* vbox_2;
    QGridLayout* grid;
    QGridLayout* grid_2;
    QGridLayout* grid_3;
    QGridLayout* grid_4;
    QGridLayout* grid_5;
    QGridLayout* grid_6;
    QGridLayout* grid_7;
    QGridLayout* grid_8;
    QGridLayout* grid_9;
    QGridLayout* grid_10;
    QGridLayout* grid_11;
    QGridLayout* grid_12;
    QGridLayout* grid_13;
    QGridLayout* grid_14;
    QGridLayout* grid_15;
    bool event( QEvent* );
};

#endif // QAGENT_H
