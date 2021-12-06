#ifndef BST_hpp
#define BST_hpp

#include "BinaryTree.hpp"
#include <vector>

template <class T>
class BST : public BinaryTree<T>
{

public:
    BST(){};
    virtual ~BST(){};

    TreeNode<T> *search(const T &) const;
    bool insert(T &);
    bool insert(TreeNode<T> *);
    void levelByLevel() const;
    void levelByLevel(TreeNode<T> *) const;
    vector<TreeNode<T> *> reverseInOrden();
    void reverseInOrden(TreeNode<T> *, vector<TreeNode<T> *> *);
    void visit(int);
    int height() const;
    int height(TreeNode<T> *node) const;

private:
    /* Ocultar algunos métodos heredados */
    //using BinaryTree<T>::insert;
};
template <class T>
TreeNode<T> *BST<T>::search(const T &value) const
{
    TreeNode<T> *aux = this->root;

    while (aux != nullptr)
    {
        if (aux->getInfo() == value)
        {
            return aux;
        }
        else
        {
            aux = aux->getInfo() > value ? aux->getLeft() : aux->getRight();
        }
    }

    return nullptr;
}

template <class T>
bool BST<T>::insert(T &value)
{
    return this->insert(new TreeNode<T>(value));
}

template <class T>
bool BST<T>::insert(TreeNode<T> *node)
{
    /* No se puede insertar un nodo NULL */
    if (node == nullptr)
        return false;

    /* Obtener la info del nodo a insertar */
    T value = node->getInfo();

    /* Establecer un apuntador auxiliar */
    TreeNode<T> *aux = this->root;

    /* Estalecer una variable para el padre */
    TreeNode<T> *parent = nullptr;

    /* Buscar la posición que le corresponde */
    while (aux != nullptr)
    {
        if (aux->getInfo() == value)
        {
            /* Liberar la memoria del nodo porque ya existe */
            delete node;

            return false;
        }
        else
        {
            parent = aux;
            aux = aux->getInfo() > value ? aux->getLeft() : aux->getRight();
        }
    }

    /* Establecer el parent del nodo a insertar */
    node->setParent(parent);

    /* Si el árbol está vacío, se inserta la raiz */
    if (parent == nullptr)
    {
        this->root = node;
    }
    else
    {
        /* Si el value a insertar es menor, se inserta a la izquierda */
        if (parent->getInfo() > value)
        {
            parent->setLeft(node);
        }
        /* Si el value a insertar es mayor, se inserta a la derecha */
        else
        {
            parent->setRight(node);
        }
    }

    return true;
}

template <class T>
void BST<T>::levelByLevel() const
{
    // Si no se pasa parametro empezar en root
    this->levelByLevel(this->root);
}

// Imprime los nodos de un arbol nivel por nivel
template <class T>
void BST<T>::levelByLevel(TreeNode<T> *node) const
{
    // Se crea queue que almacenara los nodos
    queue<TreeNode<T> *> nodes;
    // Se agrega nodo inicial
    nodes.push(node);

    // Mientras no este vacía la queue
    while (!nodes.empty())
    {
        // Agrega a la queue el nodo a la izquierda
        if (nodes.front()->getLeft() != nullptr)
        {
            nodes.push(nodes.front()->getLeft());
        }
        // Agrega a la queue el nodo a la derecha
        if (nodes.front()->getRight() != nullptr)
        {
            nodes.push(nodes.front()->getRight());
        }

        // Imprime valor de nodo actual
        cout << nodes.front()->getInfo() << " ";
        // Elimina nodo actual de la queue
        nodes.pop();
    }
}

// Desplegará cada uno de los datos almacenados en el BST dependiendo del parámetro en entrada
template <class T>
void BST<T>::visit(int option)
{
    switch (option)
    {
    case 1:
        this->preOrden();
        break;
    case 2:
        this->inOrden();
        break;
    case 3:
        this->postOrden();
        break;
    case 4:
        this->levelByLevel();
        break;
    }
}

template <class T>
int BST<T>::height() const
{
    return this->height(this->root);
}

// Muestra la altura de el BST
template <class T>
int BST<T>::height(TreeNode<T> *node) const
{
    if (node == nullptr)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->getLeft());
        int rheight = height(node->getRight());

        /* use the larger one */
        if (lheight > rheight)
        {
            return (lheight + 1);
        }
        else
        {
            return (rheight + 1);
        }
    }
}

// Procesa un BSz en forma inversa al inOrden
template <class T>
vector<TreeNode<T> *> BST<T>::reverseInOrden()
{
    // Crear apuntador a vector que recibirá los nodos
    vector<TreeNode<T> *> *top = new vector<TreeNode<T> *>;

    // Empezar función recursiva
    this->reverseInOrden(this->root, top);

    // Regresa el vector top
    return *top;
}

template <class T>
void BST<T>::reverseInOrden(TreeNode<T> *node, vector<TreeNode<T> *> *top)
{
    if (node != nullptr)
    {
        /* Desplazarse a la derecha */
        reverseInOrden(node->getRight(), top);

        /* Procesar el nodo */
        top->push_back(node);

        /* Desplazarse a la izquierda */
        reverseInOrden(node->getLeft(), top);
    }
}

#endif /* BST_hpp */