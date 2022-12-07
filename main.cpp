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
    avl_node *left;
    avl_node *right;
} * root;

/**
 *  declaramos el arbol
 */
class avl_tree {
   public:
    int height(avl_node *);
    int diff(avl_node *);
    avl_node *rr_rotation(avl_node *);
    avl_node *ll_rotation(avl_node *);
    avl_node *lr_rotation(avl_node *);
    avl_node *rl_rotation(avl_node *);
    avl_node *balance(avl_node *);
    avl_node *insert(avl_node *, int);
    void display(avl_node *, int);
    void inorder(avl_node *);
    void preorder(avl_node *);
    void postorder(avl_node *);
    avl_tree() {
        root = NULL;
    }
};

int main() {
    // obtener el root del avl
    avl_tree avl;
    vector<string> meses = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
    vector<string> abecedario = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    for (int i = 0; i < meses.size(); i++) {
        string mes = meses[i];
        int total = 0;
        for (int j = 0; j < mes.length(); j++) {
            char letra = mes[j];
            int pos = getVecPos(abecedario, string(1, letra));
            total += pos;
        }
        cout << total << endl;
        root = avl.insert(root, total);
        //avl.display(root, 1);

    }
    if (root == NULL) {
        cout << "El arbol esta vacio" << endl;
    } else {
        avl.display(root, 1);
    }
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
avl_node *avl_tree::insert(avl_node *root, int value) {
    if (root == NULL) {
        root = new avl_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    } else if (value < root->data) {
        root->left = insert(root->left, value);
        root = balance(root);
    } else if (value >= root->data) {
        root->right = insert(root->right, value);
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
            cout << "\n";
        cout << ptr->data;
        display(ptr->left, level + 1);
    }
}

/**
 * @brief avl_tree::preorder Funcion para mostrar el arbol en preorden
 *
 * @param temp
 */
void avl_tree::preorder(avl_node *temp) {
    if (root == NULL) {
        cout << "El arbol esta vacio" << endl;
        return;
    }
    if (temp != NULL) {
        cout << temp->data << " ";
        preorder(temp->left);
        preorder(temp->right);
    }
}

/**
 * @brief avl_tree::inorder Funcion para mostrar el arbol en inorden
 *
 * @param temp
 */
void avl_tree::inorder(avl_node *temp) {
    if (root == NULL) {
        cout << "El arbol esta vacio" << endl;
        return;
    }
    if (temp != NULL) {
        inorder(temp->left);
        cout << temp->data << " ";
        inorder(temp->right);
    }
}

/**
 * @brief avl_tree::postorder Funcion para mostrar el arbol en postorden
 *
 * @param temp
 */
void avl_tree::postorder(avl_node *temp) {
    if (root == NULL) {
        cout << "El arbol esta vacio" << endl;
        return;
    }
    if (temp != NULL) {
        postorder(temp->left);
        postorder(temp->right);
        cout << temp->data << " ";
    }
}