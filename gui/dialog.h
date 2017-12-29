//
//  dialog.h
//  BlockChain
//
//  Created by Chung-kaiYang on 12/29/17.
//

#ifndef dialog_h
#define dialog_h

#include <QDialog>
#include <string>

using namespace std;

class QScrollArea;
class QGridLayout;
class QLabel;
class QHBoxLayout;

class dialog : public QDialog
{
//    Q_OBJECT

public:
    dialog(QWidget *parent = 0);
    ~dialog();

    void AppendLog(const string& log);

private:
    QLabel *m_logLabel;
    QLabel *m_label1, *m_label2, *m_label3, *m_label4;

    QGridLayout *m_mainLayout;
    QHBoxLayout *m_layout1, *m_layout2;
    QScrollArea *m_scrollArea;
};

#endif /* dialog_h */
