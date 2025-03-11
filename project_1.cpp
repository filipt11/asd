#include <iostream>

using namespace std;

class TreeNode
{
public:
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};

TreeNode *insert(TreeNode *root, int data)
{
    if (root == NULL)
    {
        return new TreeNode(data);
    }
    else
    {
        TreeNode *current;
        if (data <= root->data)
        {
            current = insert(root->left, data);
            root->left = current;
        }
        else
        {
            current = insert(root->right, data);
            root->right = current;
        }
        return root;
    }
}

TreeNode *deleteTreeNode(TreeNode *root, int k)
{
    if (root == NULL)
        return root;
    if (root->data > k)
    {
        root->left = deleteTreeNode(root->left, k);
        return root;
    }
    else if (root->data < k)
    {
        root->right = deleteTreeNode(root->right, k);
        return root;
    }
    if (root->left == NULL)
    {
        TreeNode *temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL)
    {
        TreeNode *temp = root->left;
        delete root;
        return temp;
    }
    else
    {
        TreeNode *Parent = root;
        TreeNode *succ = root->right;
        while (succ->left != NULL)
        {
            Parent = succ;
            succ = succ->left;
        }

        if (Parent != root)
            Parent->left = succ->right;
        else
            Parent->right = succ->right;
        root->data = succ->data;
        delete succ;
        return root;
    }
}
void inorder(TreeNode *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(TreeNode *root)
{
    if (root == NULL)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(TreeNode *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int findMin(TreeNode *root)
{
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

int findMax(TreeNode *root)
{
    while (root->right != NULL)
        root = root->right;
    return root->data;
}

int sumLeaves(TreeNode *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return root->data;
    return sumLeaves(root->left) + sumLeaves(root->right);
}

int height(TreeNode *root)
{
    if (root == NULL)
        return -1;
    return max(height(root->left), height(root->right)) + 1;
}

TreeNode *lowestCommon(TreeNode *root, int n1, int n2)
{
    if (root == NULL)
        return NULL;

    if (root->data > n1 && root->data > n2)
        return lowestCommon(root->left, n1, n2);

    if (root->data < n1 && root->data < n2)
        return lowestCommon(root->right, n1, n2);
    return root;
}

int main()
{
    TreeNode *root = NULL;
    int n;
    int k;

    while (1)
    {
        cout << "1.Wypisz elementy drzewa w porządkach: preorder, inorder, postorder.\n";
        cout << "2.Dodaj element do drzewa\n";
        cout << "3.Usuń element drzewa\n";
        cout << "4.Wypisz wartość minimalną i maksymalną w drzewie.\n";
        cout << "5.Oblicz i wypisz sumę wartości elementów w liściach drzewa.\n";
        cout << "6.Oblicz wysokość drzewa (maksymalna liczba krawędzi od korzenia do liścia).\n";
        cout << "7.Dla dwóch podanych wartości wypisz wartość najniższego wspólnego przodka.\n";
        cout << "8.Koniec\n";
        cin >> n;
        switch (n)
        {
        case (1):
            cout << "preorder: ";
            preorder(root);
            cout << endl
                 << "inorder: ";
            inorder(root);
            cout << endl
                 << "postorder: ";
            postorder(root);
            cout << endl;
            break;
        case (2):
            cin >> k;
            root = insert(root, k);
            cout << "Dodano element do drzewa\n";
            break;
        case (3):
            cin >> k;
            root = deleteTreeNode(root, k);
            cout << "Usunieto element drzewa\n";
            break;
        case (4):
            cout << "Min: " << findMin(root) << endl;
            cout << "Max: " << findMax(root) << endl;
            break;
        case (5):
            cout << "Suma wartosci w lisciach: " << sumLeaves(root) << endl;
            break;
        case (6):
            if (height(root) == -1)
            {
                cout << "Wysokosc drzewa: 0" << endl;
            }
            else
            {
                cout << "Wysokosc drzewa: " << height(root) << endl;
            }
            break;
        case (7):
        {
            int v1, v2;
            cin >> v1 >> v2;
            TreeNode *lca = lowestCommon(root, v1, v2);
            if (lca != NULL)
                cout << "Najnizszy wspolny przodek: " << lca->data << endl;
            else
                cout << "Brak wspolnego przodka\n";
            break;
        }
        case (8):
            exit(0);
        default:
            cout << "Nieprawidlowa opcja\n";
        }
    }

    return 0;
}
