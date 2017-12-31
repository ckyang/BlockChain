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

class QApplication;
class QScrollArea;
class QGridLayout;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;

class dialog : public QDialog
{
public:
    dialog(QWidget *parent = 0, QApplication* app = 0);
    ~dialog();

    void AppendLog(const string& log);
    void UpdateBlockChainList();

private:
    QLabel *m_logLabel, *m_label1, *m_label2, *m_blockChainLabel, *m_blockChainList;

    QApplication *m_app;
    QGridLayout *m_mainLayout;
    QHBoxLayout *m_layout1;
    QVBoxLayout *m_blockChainListLayout;
    QScrollArea *m_logScrollArea, *m_blockChainScrollArea;
};

#endif /* dialog_h */
