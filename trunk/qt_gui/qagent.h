/****************************************************************************
** Form interface generated from reading ui file 'qagent.ui'
**
** Created: Wed Dec 6 15:51:36 2000
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
    QLabel* choosePathLabel;
    QButtonGroup* pathButtonGroup;
    QRadioButton* standardPathButton;
    QLabel* standardPathLabel;
    QRadioButton* advancedPathButton;
    QLabel* advancedPathLabel;
    QLabel* pressNextLabel;
    QWidget* Widget12;
    QLabel* PixmapLabel1_2_2_2_2_2_2_2_2_2_2_2;
    QComboBox* productComboBox;
    QLabel* chooseProductLabel;
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
    QLabel* useFenrisLabel;
    QFrame* Frame3;
    QLabel* fenrisLoginLabel;
    QLineEdit* LineEdit15;
    QLabel* fenrisPasswordLabel;
    QLineEdit* LineEdit16;
    QLabel* fenrisBugTextLabel;
    QMultiLineEdit* MultiLineEdit11;
    QLabel* fenrisInfoLabel;
    QCheckBox* useFenrisCheckBox;
    QWidget* Widget6;
    QCheckBox* gpgCheckBox;
    QLabel* PixmapLabel1_2_2_2_2;
    QLabel* dispatchMechanismLabel;
    QButtonGroup* dispatchMechanismGroup;
    QRadioButton* emailDispatchButton;
    QRadioButton* fileDispatchButton;
    QWidget* Widget9;
    QLabel* PixmapLabel1_2_2_2_2_2_2_2;
    QLineEdit* dumpFileEdit;
    QLabel* dumpFileLabel;
    QPushButton* chooseFileButton;
    QWidget* Widget8;
    QLabel* PixmapLabel1_2_2_2_2_2_2;
    QLabel* noGPGLabel;
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
    QGridLayout* Widget2Layout;
    QGridLayout* Widget13Layout;
    QVBoxLayout* pathButtonGroupLayout;
    QGridLayout* Widget12Layout;
    QGridLayout* Widget3Layout;
    QGridLayout* Widget4Layout;
    QGridLayout* Widget5Layout;
    QGridLayout* Widget7Layout;
    QGridLayout* Widget14Layout;
    QGridLayout* Frame3Layout;
    QGridLayout* Widget6Layout;
    QVBoxLayout* dispatchMechanismGroupLayout;
    QGridLayout* Widget9Layout;
    QGridLayout* Widget8Layout;
    QGridLayout* Widget12Layout_2;
    QGridLayout* Widget10Layout;
    QGridLayout* Widget11Layout;
    bool event( QEvent* );
};

#endif // QAGENT_H
