#pragma once
#include <iostream>
using namespace std;
#define MAX(a,b)  (a) > (b) ? (a) : (b)

template<typename TYPE>
class CMyAVLTree
{
public:
    class TreeNode
    {
    public:
        TreeNode(const TYPE& elem,
                 TreeNode *parent = nullptr,
                 unsigned int height = 0, 
                 TreeNode *left = nullptr, 
                 TreeNode *right = nullptr, 
                 TreeNode *next = nullptr)
                 :elem_(elem), parent_(parent), height_(height), left_(left), right_(right), next_(next)
        {
        }

        TreeNode(const TYPE&& elem,
                 TreeNode *parent = nullptr,
                 unsigned int height = 0,
                 TreeNode *left = nullptr,
                 TreeNode *right = nullptr,
                 TreeNode *next = nullptr)
            :elem_(std::move(elem)), parent_(parent), height_(height), left_(left), right_(right), next_(next)
        {
        }
        ~TreeNode()
        {
            if (next_ != nullptr)
            {
                delete next_;
            }
        }

        TYPE elem_;           //����
        TreeNode *parent_;    //���ڵ�
        unsigned int height_; //���ĸ߶�
        TreeNode *left_;      //������
        TreeNode *right_;     //������
        TreeNode *next_;      //����
    };
public:
    CMyAVLTree();
    ~CMyAVLTree();
    bool IsEmpty();                    //�ж��Ƿ�Ϊ����
    TreeNode *find(TYPE &elem)   //��������
    {
        TreeNode *node = root_;
        if (IsEmpty())
        {
            return nullptr;
        }

        while (node)
        {
            //С�ڽڵ�����ȥ����������
            if (pfnCompare_(elem, node->elem_) < 0)
            {
                node = node->left_;
            }
            //���ڽڵ�����ȥ��������
            else if (pfnCompare_(elem, node->elem_) > 0)
            {
                node = node->right_;
            }
            //�ҵ����ؽڵ�
            else
            {
                return node;
            }
        }

        return nullptr;
    }
    
    //����ָ��(����ָ�����ֱȽϺ�����ID�ȽϺ����ֱȽϣ�
    typedef int (*pfnCompare)(TYPE &obj1,TYPE &obj2);
    pfnCompare pfnCompare_ = nullptr;

    void insert(TYPE &elem);     //��������
    void remove(const TYPE &elem);     //ɾ������
    //ǰ�����

    //�������

    //�������

    //�������

private:
    //��ȡ�ڵ�ĸ߶�
    int getHeight(TreeNode *node);
    //��ת
    //����ת
    void rotateWithLeft(TreeNode *K1);
    //�ҵ���ת
    void rotateWithRight(TreeNode *K1);
    //��˫��ת
    void doubleRotateLeft(TreeNode *node);
    //��˫��ת
    void doubleRotateRight(TreeNode *node);
    //ƽ��
    void balance(TreeNode *node);
    //�ҵ�ǰ�ڵ���������С�Ľڵ�
    TreeNode* findMin(TreeNode *node)
    {
        if (node == nullptr)
        {
            throw "CMyAVLTree::finMin is empty";
        }

        while (node->left_)
        {
            node = node->left_;
        }

        return node;
    }
    //�Ƴ���
    void removeTree();

private:
    TreeNode *root_;     //���ڵ�
};

template<typename TYPE>
CMyAVLTree<TYPE>::CMyAVLTree()
:root_(nullptr)
{
}

template<typename TYPE>
CMyAVLTree<TYPE> ::~CMyAVLTree()
{
    removeTree();
}

/*
�ж��Ƿ��ǿ���
�޲���
����ֵ�����ڵ�Ϊ�գ�����ֵΪ��
*/
template<typename TYPE>
bool CMyAVLTree<TYPE>::IsEmpty()
{
    return root_ == nullptr;
}

template<typename TYPE>
void CMyAVLTree<TYPE> ::insert(TYPE &elem)
{
    //����ǿ�����ֱ�Ӳ���Ϊ���ڵ�
    if (IsEmpty())
    {
        root_ = new TreeNode(elem);
        return;
    }

    TreeNode *node = root_;
    while (true)
    {
        //С�ڽڵ�����ȥ������
        if (pfnCompare_(elem, node->elem_) < 0)
        {
            //�ڵ�û������
            if (node->left_ == nullptr)
            {
                //����Ϊ�ڵ�����ӣ����ڵ���Ϊ���ӵĸ��ڵ�
                node->left_ = new TreeNode(elem,node);
                balance(node);
                return;
            }
            node = node->left_;
        }
        //���ڽڵ�����ȥ������
        else if (pfnCompare_(elem, node->elem_) > 0)
        {
            //�ڵ�û���Һ���
            if (node->right_ == nullptr)
            {
                //����Ϊ�ڵ���Һ���,���ڵ���Ϊ�Һ��ӵĸ��ڵ�
                node->right_ = new TreeNode(elem,node);
                balance(node);
                return;
            }
            node = node->right_;
        }
        //������������ͬ�����ݣ���������
        else
        {
            //[1][nullptr]
            //[1][2][nullptr]
            //[1][3][2][nullptr]
            //[1][4][3][2][nullptr]
            TreeNode *newNode = new TreeNode(elem, node);
            newNode->next_ = node->next_;
            node->next_ = newNode;
            return;
        }
    }
}

template<typename TYPE>
void CMyAVLTree<TYPE>::remove(const TYPE &elem)
{
    //����ǿ�������
    if (IsEmpty())
    {
        return;
    }

    TYPE origin = elem;
    TreeNode *node = root_;
    while (node != nullptr)
    {
        //���С�ڵ�ǰ�ڵ����ݣ�ȥ�����
        if (pfnCompare_(origin, node->elem_) < 0)
        {
            node = node->left_;
        }
        //������ڵ�ǰ�ڵ����ݣ�ȥ�ұ���
        else if (pfnCompare_(origin, node->elem_) > 0)
        {
            node = node->right_;
        }
        //�ж��Ƿ���Ҷ�ӽڵ�
        else if (node->left_ == nullptr&&node->right_ == nullptr)
        {
            TreeNode *parent = node->parent_;
            //������Ǹ��ڵ�
            if (parent != nullptr)
            {
                //����Ǹ��ڵ�����ӣ������ÿ�
                if (node == parent->left_)
                {
                    parent->left_ = nullptr;
                }
                //����Ǹ��ڵ���Һ��ӣ��Һ����ÿ�
                else if (node == parent->right_)
                {
                    parent->right_ = nullptr;
                }

                //ƽ����
                balance(parent);
            }
            //����Ǹ��ڵ㣬ֱ�ӰѸ��ڵ��ÿ�
            else
            {
                root_ = nullptr;
            }

            delete node;
            return;
        }
        //�ж���һ������
        else if (node->left_ == nullptr || node->right_ == nullptr)
        {
            TreeNode *parent = node->parent_;
            TreeNode *child = (node->left_ == nullptr ? node->right_ : node->left_);
            //������Ǹ��ڵ�
            if (parent != nullptr)
            {
                //����Ǹ��ڵ�����ӣ��Ѻ�����Ϊ���ڵ������
                if (node == parent->left_)
                {
                    parent->left_ = child;
                }
                //����Ǹ��ڵ���Һ��ӣ��Ѻ�����Ϊ���ڵ���Һ���
                else if (node == parent->right_)
                {
                    parent->right_ = child;
                }
            }
            //����Ǹ��ڵ㣬�Ѻ�����Ϊ���ڵ�
            else
            {
                root_ = child;
            }
            //���ӵĸ��׸�Ϊ���ڵ�
            child->parent_ = parent;

            //ƽ��
            balance(parent);
            delete node;
            return;
        }
        //�ж�����������
        else
        {
            //�ҵ��ұ���С�Ľڵ�
            TreeNode *minNode = findMin(node->right_);
            //����Сֵ���ǵ�ǰ�ڵ��ֵ
            node->elem_ = minNode->elem_;

            //��������
            TreeNode *next = node->next_;
            node->next_ = minNode->next_;
            minNode->next_ = next;

            node = minNode;
            //��Ҫɾ���ĸ�Ϊ
            origin = node->elem_;
        }
    }
}

/*
��ȡ�ڵ�ĸ߶�
����һ���ڵ�
����ֵ���ڵ�߶�
*/
template<typename TYPE>
int CMyAVLTree<TYPE>::getHeight(TreeNode *node)
{
    return node == nullptr ? 0 : node->height_;
}

/*
����ת
����һ���ڵ�
�޷���ֵ
*/
template<typename TYPE>
void CMyAVLTree<TYPE>::rotateWithLeft(TreeNode *K1)
{
    //��תǰ
    TreeNode *P = K1->parent_;
    TreeNode *A = K1->left_;
    TreeNode *K2 = K1->right_;
    TreeNode *B = K2->left_;
    TreeNode *C = K2->right_;

    //��ת��
    K1->parent_ = K2;
    K1->right_ = B;
    K2->parent_ = P;
    K2->left_ = K1;
    //���B�ڵ���ڣ�B�ڵ�ĸ��ڵ����
    if (B != nullptr)
    {
        B->parent_ = K1;
    }

    //��ת�����µ����ڵ�ĸ߶�
    K1->height_ = MAX(getHeight(A), getHeight(B)) + 1;
    K2->height_ = MAX(getHeight(K1), getHeight(C)) + 1;
    
    //�����תǰK1�и��ڵ�
    if (P != nullptr)
    {
        //�����תǰK1�Ǹ��ڵ����ӣ���ת��K2�Ǹ��ڵ�����
        if (P->left_ == K1)
        {
            P->left_ = K2;
            return;
        }
        //�����תǰK1�Ǹ��ڵ��Һ��ӣ���ת��K2�Ǹ��ڵ��Һ���
        else
        {
            P->right_ = K2;
            return;
        }
    }
    //�����תǰK1û�и��ڵ㣨���ڵ㣩����ת��K2�Ǹ��ڵ�
    else
    {
        root_ = K2;
    }
}

/*
�ҵ���ת
����һ���ڵ�
�޷���ֵ
*/
template<typename TYPE>
void CMyAVLTree<TYPE>::rotateWithRight(TreeNode *K1)
{
    //��תǰ
    TreeNode *P = K1->parent_;
    TreeNode *K2 = K1->left_;
    TreeNode *A = K2->left_;
    TreeNode *B = K2->right_;
    TreeNode *C = K1->right_;

    //��ת��
    K1->left_ = B;
    K1->parent_ = K2;
    K2->right_ = K1;
    K2->parent_ = P;
    //���B�ڵ���ڣ�B�ڵ�ĸ��ڵ����
    if (B != nullptr)
    {
        B->parent_ = K1;
    }

    //��ת�����µ����߶�
    K1->height_ = MAX(getHeight(B), getHeight(C)) + 1;
    K2->height_ = MAX(getHeight(A), getHeight(K1)) + 1;

    //�����תǰK1�и��ڵ�
    if (P != nullptr)
    {
        //�����תǰK1�Ǹ��ڵ����ӣ���ת��K2�Ǹ��ڵ�����
        if (P->left_ == K1)
        {
            P->left_ = K2;
            return;
        }
        //�����תǰK1�Ǹ��ڵ��Һ��ӣ���ת��K2�Ǹ��ڵ��Һ���
        else
        {
            P->right_ = K2;
            return;
        }
    }
    //�����תǰK1û�и��ڵ㣨���ڵ㣩����ת��K2�Ǹ��ڵ�
    else
    {
        root_ = K2;
    }
}

template<typename TYPE>
void CMyAVLTree<TYPE>::doubleRotateLeft(TreeNode *node)
{
    //�Ƚ��ڵ����������ת
    rotateWithLeft(node->left_);
    //�ٽ��ڵ��ҵ���ת
    rotateWithRight(node);
}

template<typename TYPE>
void CMyAVLTree<TYPE>::doubleRotateRight(TreeNode *node)
{
    //�Ƚ��ڵ���Һ����ҵ���ת
    rotateWithRight(node->right_);
    //�ٽ��ڵ�����ת
    rotateWithLeft(node);
}

template<typename TYPE>
void CMyAVLTree<TYPE>::balance(TreeNode *node)
{
    while (node != nullptr)
    {
        //�����߶�
        node->height_ = MAX(getHeight(node->left_), getHeight(node->right_)) + 1;

        //���������������ĸ߶Ȳ�
        int subHeight = getHeight(node->left_) - getHeight(node->right_);
        //��������
        if (subHeight > 1)
        {
            subHeight = getHeight(node->left_->left_) - getHeight(node->left_->right_);

            /*
                 A                    B
               B         >>>>      C     A
             C
            */
            if (subHeight > 0)
            {
                //�ҵ���ת
                rotateWithRight(node);
            }
            /*
                 A                   A                   C
               B         >>>>      C         >>>>     B     A  
                C                B
            */
            else if (subHeight < 0)
            {
                //��˫��ת
                doubleRotateLeft(node);
            }
        }
        //��������
        else if (subHeight < -1)
        {
            subHeight = getHeight(node->right_->left_) - getHeight(node->right_->right_);

            /*
            A                        B
              B         >>>>      A    C
                C
            */
            if (subHeight < 0)
            {
                //����ת
                rotateWithLeft(node);
            }
            /*
            A                   A                       C
              B         >>>>      C         >>>>     A     B
             C                      B
            */
            else if (subHeight > 0)
            {
                //��˫��ת
                doubleRotateRight(node);
            }
        }
        node = node->parent_;
    }
}

template<typename TYPE>
void CMyAVLTree<TYPE>::removeTree()
{
    if (root_ == nullptr)
    {
        return;
    }

    TreeNode *node = root_;
    while (node)
    {
        //����ڵ�û�к���
        if (node->left_ == nullptr&&node->right_ == nullptr)
        {
            //����ڵ��Ǹ��ڵ��ֱ��ɾ��
            if (node == root_)
            {
                delete node;
                return;
            }

            TreeNode *old = node;
            node = node->parent_;
            //����ڵ��Ǹ��ڵ������
            if (old == node->left_)
            {
                //�������ÿ�
                node->left_ = nullptr;
            }
            //����ڵ��Ǹ��ڵ���Һ���
            else
            {
                //���Һ����ÿ�
                node->right_ = nullptr;
            }
            //����ڵ��������������
            TreeNode *linkNode = old->next_;
            while (linkNode != nullptr)
            {
                TreeNode *oldLink = linkNode;
                linkNode = linkNode->next_;
                delete oldLink;
            }
            //ɾ���ڵ�
            delete old;
            
        }
        //����ڵ��к��ӣ���ȥ���
        else if (node->left_ != nullptr)
        {
            node = node->left_;
        }
        //��ȥ�ұ�
        else if (node->right_ != nullptr)
        {
            node = node->right_;
        }
    }
}

