#include "List.h"

List::List() {
    head = nullptr;
}
List::List(List &lista) {
    head = nullptr;
    Node* pAux = lista.head;
    while (pAux != nullptr) {
        insertTail(pAux->getInfo());
        pAux = pAux->getPtrNext();
    }
}
List::~List() {

}
bool List::isEmpty() {
    return !head ? true : false;
}
void List::display() {
    Node* pAux = head;
    if (isEmpty()) {
        cout << "Lista vuota" << endl;
    } else {
        while (pAux != nullptr) {
            cout << pAux->getInfo();
            pAux = pAux->getPtrNext();
        }
    }
    
} //scansione della list
bool List::insertHead(int data) {
    Node* pNew = new Node(data, head);
    if (!pNew) {
        cerr << "Allocazione fallita";
        return false;
    }
    head = pNew;
    return true;
}

bool List::insertTail(int data) {
    Node* pNew = new Node(data);
    if (!pNew) {
        cerr << "Allocazione fallita";
        return false;
    }
    if (isEmpty()) {
        head = pNew;
    } else {
        Node* pAux = head;
        while (pAux->getPtrNext() != nullptr) {
            pAux = pAux->getPtrNext();
        }
        pAux->setPtrNext(pNew);
    }
    return true;
}

void List::displayRec(Node* head) {
    if (head != nullptr) {
        //Passo
        cout << " " << head->getInfo();
        displayRec(head->getPtrNext());
    }
    //Base: lista vuota
}

void List::displayHelper() {
    displayRec(head);
}

// Node* List::getHead() {
//     return head;
// }

bool List::remove(int data) {
    bool flag = false;
    if (!isEmpty()) {
        Node* pCancel;
        if (data == head->getInfo()) {
            pCancel = head;
            head = head->getPtrNext();
            delete pCancel;
            flag = true;
        } else {
            Node* pCurrent;
            pCancel = head->getPtrNext();
            pCurrent = head;
            while (pCancel != nullptr && pCurrent->getInfo() != data) {
                pCancel = pCancel->getPtrNext();
                pCurrent = pCurrent->getPtrNext();
            }
            if (pCancel != nullptr) {
                pCurrent->setPtrNext(pCancel->getPtrNext());
                delete pCancel;
                flag = true;
            }
        }
    }
    return flag;
}

void List::ordina() {
    /*Ordinamento ingenuo*/
    // for (int i = 0; i < dim - 1; i++) {
    //     for (int y = i; y < dim; y++) {
    //         if (arr[i] < arr[y]) {
    //             int temp = arr[i];
    //             arr[i] = arr[y];
    //             arr[y] = temp;
    //         }
    //     }
    // }

    
    if (!isEmpty()) {
        Node* pi = head, *pj;
        while (pi->getPtrNext() != nullptr) {
            pj = pi->getPtrNext();
            while (pj != nullptr) {
                if (pi->getInfo() > pj->getInfo()) {
                    swap(pi, pj);
                }
            }
            pi = pi->getPtrNext();
        }
    } else {
        cout << "Lista vuota";
    }
}

void List::swap(Node* pi, Node* pj) {
    int temp = pi->getInfo();
    pi->setInfo(pj->getInfo());
    pj->setInfo(temp);
}

istream& operator>>(istream& in, List* l1) {
    int n, value;
    cout << "Inserisci il n elementi: ";
    in >> n;
    for (int  i = 0; i < n; i++) {
        in >> value;
       cout << !l1->insertTail(value) && "Allocazione fallita";
    }
    return in;
}

List& List::operator+(List& l1) {
    Node* pAux = head;
    if (!isEmpty()) {
        while (pAux->getPtrNext()) {
            pAux = pAux->getPtrNext();
        }
        pAux->setPtrNext(l1.head);
    } else {
        head = l1.head;
    }
    l1.head = nullptr;
    return *this;
}

List megaOrdinamento(List& l1, List& l2) {
    List fusione;

    l1.ordina();
    l2.ordina();

    Node *pi, *pj;
    pi = l1.head;
    pj = l2.head;

    while (pi != nullptr && pj != nullptr) {
        if (pi->getInfo() < pj->getInfo()) {
            fusione.insertTail(pi->getInfo());
            pi = pi->getPtrNext();
        } else {
            fusione.insertTail(pj->getInfo());
            pj = pj->getPtrNext();
        }
    }

    while (pi != nullptr) {
        fusione.insertTail(pi->getInfo());
        pi = pi->getPtrNext();
    }
    
    while (pj != nullptr) {
        fusione.insertTail(pj->getInfo());
        pj = pj->getPtrNext();
    }

    return fusione;
}