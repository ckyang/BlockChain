//
//  factory.h
//  BlockChain
//
//  Created by Chung-kaiYang on 12/17/17.
//  Copyright © 2017 Chung-kaiYang. All rights reserved.
//

#ifndef factory_h
#define factory_h

class blockChain;
class talk;
class crypto;
class dialog;
class QApplication;

class factory
{
public:
    ~factory();

    static blockChain* GetBlockChain();
    static talk* GetTalk();
    static crypto* GetCrypto();
    static dialog* GetDialog(QApplication *app = 0);

private:
    static blockChain* m_blockChain;
    static talk* m_talk;
    static crypto* m_crypto;
    static dialog* m_dialog;
};

#endif /* factory_h */
