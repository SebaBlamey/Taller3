#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include<iomanip>
#include<cmath>

using namespace std;
int getVecPos(vector<string>, string);

struct avl_node {
    int data;
    int id;
    avl_node *left;
    avl_node *right;
} * root;

/**
 *  declaramos el arbol
 */


class mes{
    private:
        string nombre;
        int peso;
    public:
        mes(string nombre,int peso){
            this->nombre = nombre;
            this->peso = peso;
        }
        string imprimir(){
            cout << "Mes: " << nombre << "Pesos: " << peso << endl; 
        }
        
};

class avl_tree {
   public:
    int height(avl_node *);
    int diff(avl_node *);
    avl_node *rr_rotation(avl_node *);
    avl_node *ll_rotation(avl_node *);
    avl_node *lr_rotation(avl_node *);
    avl_node *rl_rotation(avl_node *);
    avl_node *balance(avl_node *);
    avl_node *insert(avl_node *, int,int);
    void display(avl_node *, int);
    void inorder(avl_node *,vector<string>);
    void preorder(avl_node *,vector<string>);
    void postorder(avl_node *,vector<string>);
    avl_tree() {
        root = NULL;
    }
};

int main() {
    // obtener el root del avl
 
    avl_tree avl;
    vector<string> meses = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
    vector<string> abecedario = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    vector<int> pesos = {0,0,0,0,0,0,0,0,0,0,0,0};
    for (int i = 0; i < meses.size(); i++) {
        string mes = meses[i];
        int total = 0;
        for (int j = 0; j < mes.length(); j++) {
            char letra = mes[j];
            int pos = getVecPos(abecedario, string(1, letra));
            total += pos;
        }
        
        
        pesos[i] = total;
        cout << total << endl;
        
        //avl.display(root, 1);

    }
    for (int i = 0; i < meses.size(); i++)
    {
       for (int j = i+1; j < meses.size(); j++)
       {
        if(pesos[i] == pesos[j]){
            pesos[j] = pesos[i] - 1;
        }
       }
       root = avl.insert(root, pesos[i],i);
    }
    
   

    cout << "---------ALGORITMO HINDU DE COMPARACION------------"<<endl;
    for (int i = 0; i < meses.size(); i++)
    {
        cout << pesos[i] <<endl;
    }
    cout << "---------------------"<<endl;


    if (root == NULL) {
        cout << "El arbol esta vacio" << endl;
    } else {
        avl.display(root, 1);
    }

   cout << endl;
    cout << "IN ORDER" << endl << "------------" << endl;
    avl.inorder(root,meses);
    cout <<endl;
    cout <<endl;
    cout << "PRE ORDER" << endl << "------------" << endl;
    avl.preorder(root,meses);
    cout <<endl;
    cout <<endl;
    cout << "POST ORDER" << endl << "------------" << endl;
    avl.postorder(root,meses);
    cout <<endl;
    cout <<endl;
    return 0;
}
int getVecPos(vector<string> arr, string name) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == name) {
            return i + 1;
        }
    }
    return -1;
}

/**
 * @brief avl_tree::height Funcion para obtener la altura del arbol
 *
 * @param temp
 * @return int
 */
int avl_tree::height(avl_node *temp) {
    int h = 0;
    if (temp != NULL) {
        int l_height = height(temp->left);
        int r_height = height(temp->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

/**
 * @brief avl_tree::diff Funcion para obtener la diferencia de altura entre los nodos
 *
 * @param temp
 * @return int
 */
int avl_tree::diff(avl_node *temp) {
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    int b_factor = l_height - r_height;
    return b_factor;
}

/**
 * @brief avl_tree::rr_rotation Funcion para rotar a la derecha
 *
 * @param parent
 * @return avl_node*
 */
avl_node *avl_tree::rr_rotation(avl_node *parent) {
    avl_node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

/**
 * @brief avl_tree::ll_rotation Funcion para rotar a la izquierda
 *
 * @param parent
 * @return avl_node*
 */
avl_node *avl_tree::ll_rotation(avl_node *parent) {
    avl_node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

/**
 * @brief avl_tree::lr_rotation Funcion para rotar a la izquierda y luego a la derecha
 *
 * @param parent
 * @return avl_node*
 */
avl_node *avl_tree::lr_rotation(avl_node *parent) {
    avl_node *temp;
    temp = parent->left;
    parent->left = rr_rotation(temp);
    return ll_rotation(parent);
}

/**
 * @brief avl_tree::rl_rotation Funcion para rotar a la derecha y luego a la izquierda
 *
 * @param parent
 * @return avl_node*
 */
avl_node *avl_tree::rl_rotation(avl_node *parent) {
    avl_node *temp;
    temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
}

/**
 * @brief avl_tree::balance Funcion para balancear el arbol
 *
 * @param temp
 * @return avl_node*
 */
avl_node *avl_tree::balance(avl_node *temp) {
    int bal_factor = diff(temp);
    if (bal_factor > 1) {
        if (diff(temp->left) > 0)
            temp = ll_rotation(temp);
        else
            temp = lr_rotation(temp);
    } else if (bal_factor < -1) {
        if (diff(temp->right) > 0)
            temp = rl_rotation(temp);
        else
            temp = rr_rotation(temp);
    }
    return temp;
}

/**
 * @brief avl_tree::insert Funcion para insertar un nodo en el arbol
 *
 * @param root
 * @param value
 * @return avl_node*
 */
avl_node *avl_tree::insert(avl_node *root, int value,int id) {
    if (root == NULL) {
        root = new avl_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        root->id = id;
        return root;
    } else if (value < root->data) {
        root->left = insert(root->left, value,id);
        root = balance(root);
    } else if (value >= root->data) {
        root->right = insert(root->right, value,id);
        root = balance(root);
    }
    return root;
}
/**
 * @brief avl_tree::display Funcion para mostrar el arbol
 * 
 */
void avl_tree::display(avl_node *ptr, int level) {
    int i;
    if (ptr != NULL) {
        display(ptr->right, level + 1);
        cout << endl;
        if (ptr == root)
            cout << "Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout << "        ";
        cout << ptr->data;
        display(ptr->left, level + 1);
    }
}

/**
 * @brief avl_tree::preorder Funcion para mostrar el arbol en preorden
 *
 * @param temp
 */
void avl_tree::preorder(avl_node *temp,vector<string> meses) {
    if (root == NULL) {
        cout << "El arbol esta vacio" << endl;
        return;
    }
    if (temp != NULL) {
        cout << meses[temp->id] << " ";
        preorder(temp->left,meses);
        preorder(temp->right,meses);
    }
}

/**
 * @brief avl_tree::inorder Funcion para mostrar el arbol en inorden
 *
 * @param temp
 */
void avl_tree::inorder(avl_node *temp,vector<string> meses) {
    if (root == NULL) {
        cout << "El arbol esta vacio" << endl;
        return;
    }
    if (temp != NULL) {
        inorder(temp->left,meses);
        cout << meses[temp->id] << " ";
        inorder(temp->right,meses);
    }
}

/**
 * @brief avl_tree::postorder Funcion para mostrar el arbol en postorden
 *
 * @param temp
 */
void avl_tree::postorder(avl_node *temp,vector<string> meses) {
    if (root == NULL) {
        cout << "El arbol esta vacio" << endl;
        return;
    }
    if (temp != NULL) {
        postorder(temp->left,meses);
        postorder(temp->right,meses);
        cout << meses[temp->id] << " ";
    }
}