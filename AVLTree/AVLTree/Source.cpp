#include <iostream>
#include <stdlib.h>
#include "AVLTree.h"
int main() {
    AVLTree<int>* MyAVL = new AVLTree<int>();
    auto Prnt = [](int h) { cout<< h <<" "; };
    
    MyAVL->Add(14);
    MyAVL->Add(8);
    MyAVL->Add(21);
    MyAVL->Add(4);
    MyAVL->Add(16);
    MyAVL->Add(31);
    MyAVL->Add(1);
    MyAVL->Add(99);
    MyAVL->Add(44);
    MyAVL->Add(104);
    MyAVL->Add(32);
    MyAVL->Add(19);
    MyAVL->Add(13);

    cout<<endl;

    cout<<"El tamanio es: "<< MyAVL->Size()<<endl;
    cout<<"La altura es: "<< MyAVL->Height()<<endl;   
    cout<<"Inorder: "; MyAVL->Inorder(Prnt); cout<<endl;
     
    delete MyAVL;
    return 0;
}
