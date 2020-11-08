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

        TYPE elem_;           //数据
        TreeNode *parent_;    //父节点
        unsigned int height_; //树的高度
        TreeNode *left_;      //左子树
        TreeNode *right_;     //右子树
        TreeNode *next_;      //链表
    };
public:
    CMyAVLTree();
    ~CMyAVLTree();
    bool IsEmpty();                    //判断是否为空树
    TreeNode *find(TYPE &elem)   //查找数据
    {
        TreeNode *node = root_;
        if (IsEmpty())
        {
            return nullptr;
        }

        while (node)
        {
            //小于节点数据去左子树查找
            if (pfnCompare_(elem, node->elem_) < 0)
            {
                node = node->left_;
            }
            //大于节点数据去右子树找
            else if (pfnCompare_(elem, node->elem_) > 0)
            {
                node = node->right_;
            }
            //找到返回节点
            else
            {
                return node;
            }
        }

        return nullptr;
    }
    
    //函数指针(用于指向两种比较函数：ID比较和名字比较）
    typedef int (*pfnCompare)(TYPE &obj1,TYPE &obj2);
    pfnCompare pfnCompare_ = nullptr;

    void insert(TYPE &elem);     //插入数据
    void remove(const TYPE &elem);     //删除数据
    //前序遍历

    //中序遍历

    //后序遍历

    //层序遍历

private:
    //获取节点的高度
    int getHeight(TreeNode *node);
    //旋转
    //左单旋转
    void rotateWithLeft(TreeNode *K1);
    //右单旋转
    void rotateWithRight(TreeNode *K1);
    //左双旋转
    void doubleRotateLeft(TreeNode *node);
    //右双旋转
    void doubleRotateRight(TreeNode *node);
    //平衡
    void balance(TreeNode *node);
    //找当前节点下数据最小的节点
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
    //移除树
    void removeTree();

private:
    TreeNode *root_;     //根节点
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
判断是否是空树
无参数
返回值当根节点为空，返回值为真
*/
template<typename TYPE>
bool CMyAVLTree<TYPE>::IsEmpty()
{
    return root_ == nullptr;
}

template<typename TYPE>
void CMyAVLTree<TYPE> ::insert(TYPE &elem)
{
    //如果是空树，直接插入为根节点
    if (IsEmpty())
    {
        root_ = new TreeNode(elem);
        return;
    }

    TreeNode *node = root_;
    while (true)
    {
        //小于节点数据去左子树
        if (pfnCompare_(elem, node->elem_) < 0)
        {
            //节点没有左孩子
            if (node->left_ == nullptr)
            {
                //插入为节点的左孩子，将节点作为左孩子的父节点
                node->left_ = new TreeNode(elem,node);
                balance(node);
                return;
            }
            node = node->left_;
        }
        //大于节点数据去右子树
        else if (pfnCompare_(elem, node->elem_) > 0)
        {
            //节点没有右孩子
            if (node->right_ == nullptr)
            {
                //插入为节点的右孩子,将节点作为右孩子的父节点
                node->right_ = new TreeNode(elem,node);
                balance(node);
                return;
            }
            node = node->right_;
        }
        //插入与树中相同的数据，用链表保存
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
    //如果是空树返回
    if (IsEmpty())
    {
        return;
    }

    TYPE origin = elem;
    TreeNode *node = root_;
    while (node != nullptr)
    {
        //如果小于当前节点数据，去左边找
        if (pfnCompare_(origin, node->elem_) < 0)
        {
            node = node->left_;
        }
        //如果大于当前节点数据，去右边找
        else if (pfnCompare_(origin, node->elem_) > 0)
        {
            node = node->right_;
        }
        //判断是否是叶子节点
        else if (node->left_ == nullptr&&node->right_ == nullptr)
        {
            TreeNode *parent = node->parent_;
            //如果不是根节点
            if (parent != nullptr)
            {
                //如果是父节点的左孩子，左孩子置空
                if (node == parent->left_)
                {
                    parent->left_ = nullptr;
                }
                //如果是父节点的右孩子，右孩子置空
                else if (node == parent->right_)
                {
                    parent->right_ = nullptr;
                }

                //平衡树
                balance(parent);
            }
            //如果是根节点，直接把根节点置空
            else
            {
                root_ = nullptr;
            }

            delete node;
            return;
        }
        //判断有一个孩子
        else if (node->left_ == nullptr || node->right_ == nullptr)
        {
            TreeNode *parent = node->parent_;
            TreeNode *child = (node->left_ == nullptr ? node->right_ : node->left_);
            //如果不是根节点
            if (parent != nullptr)
            {
                //如果是父节点的左孩子，把孩子作为父节点的左孩子
                if (node == parent->left_)
                {
                    parent->left_ = child;
                }
                //如果是父节点的右孩子，把孩子作为父节点的右孩子
                else if (node == parent->right_)
                {
                    parent->right_ = child;
                }
            }
            //如果是根节点，把孩子作为根节点
            else
            {
                root_ = child;
            }
            //孩子的父亲改为父节点
            child->parent_ = parent;

            //平衡
            balance(parent);
            delete node;
            return;
        }
        //判断有两个孩子
        else
        {
            //找到右边最小的节点
            TreeNode *minNode = findMin(node->right_);
            //用最小值覆盖当前节点的值
            node->elem_ = minNode->elem_;

            //交换链表
            TreeNode *next = node->next_;
            node->next_ = minNode->next_;
            minNode->next_ = next;

            node = minNode;
            //把要删除的改为
            origin = node->elem_;
        }
    }
}

/*
获取节点的高度
参数一：节点
返回值：节点高度
*/
template<typename TYPE>
int CMyAVLTree<TYPE>::getHeight(TreeNode *node)
{
    return node == nullptr ? 0 : node->height_;
}

/*
左单旋转
参数一：节点
无返回值
*/
template<typename TYPE>
void CMyAVLTree<TYPE>::rotateWithLeft(TreeNode *K1)
{
    //旋转前
    TreeNode *P = K1->parent_;
    TreeNode *A = K1->left_;
    TreeNode *K2 = K1->right_;
    TreeNode *B = K2->left_;
    TreeNode *C = K2->right_;

    //旋转后
    K1->parent_ = K2;
    K1->right_ = B;
    K2->parent_ = P;
    K2->left_ = K1;
    //如果B节点存在，B节点的父节点改了
    if (B != nullptr)
    {
        B->parent_ = K1;
    }

    //旋转后，重新调整节点的高度
    K1->height_ = MAX(getHeight(A), getHeight(B)) + 1;
    K2->height_ = MAX(getHeight(K1), getHeight(C)) + 1;
    
    //如果旋转前K1有父节点
    if (P != nullptr)
    {
        //如果旋转前K1是父节点左孩子，旋转后K2是父节点左孩子
        if (P->left_ == K1)
        {
            P->left_ = K2;
            return;
        }
        //如果旋转前K1是父节点右孩子，旋转后K2是父节点右孩子
        else
        {
            P->right_ = K2;
            return;
        }
    }
    //如果旋转前K1没有父节点（根节点），旋转后K2是根节点
    else
    {
        root_ = K2;
    }
}

/*
右单旋转
参数一：节点
无返回值
*/
template<typename TYPE>
void CMyAVLTree<TYPE>::rotateWithRight(TreeNode *K1)
{
    //旋转前
    TreeNode *P = K1->parent_;
    TreeNode *K2 = K1->left_;
    TreeNode *A = K2->left_;
    TreeNode *B = K2->right_;
    TreeNode *C = K1->right_;

    //旋转后
    K1->left_ = B;
    K1->parent_ = K2;
    K2->right_ = K1;
    K2->parent_ = P;
    //如果B节点存在，B节点的父节点改了
    if (B != nullptr)
    {
        B->parent_ = K1;
    }

    //旋转后重新调整高度
    K1->height_ = MAX(getHeight(B), getHeight(C)) + 1;
    K2->height_ = MAX(getHeight(A), getHeight(K1)) + 1;

    //如果旋转前K1有父节点
    if (P != nullptr)
    {
        //如果旋转前K1是父节点左孩子，旋转后K2是父节点左孩子
        if (P->left_ == K1)
        {
            P->left_ = K2;
            return;
        }
        //如果旋转前K1是父节点右孩子，旋转后K2是父节点右孩子
        else
        {
            P->right_ = K2;
            return;
        }
    }
    //如果旋转前K1没有父节点（根节点），旋转后K2是根节点
    else
    {
        root_ = K2;
    }
}

template<typename TYPE>
void CMyAVLTree<TYPE>::doubleRotateLeft(TreeNode *node)
{
    //先将节点的左孩子左单旋转
    rotateWithLeft(node->left_);
    //再将节点右单旋转
    rotateWithRight(node);
}

template<typename TYPE>
void CMyAVLTree<TYPE>::doubleRotateRight(TreeNode *node)
{
    //先将节点的右孩子右单旋转
    rotateWithRight(node->right_);
    //再将节点左单旋转
    rotateWithLeft(node);
}

template<typename TYPE>
void CMyAVLTree<TYPE>::balance(TreeNode *node)
{
    while (node != nullptr)
    {
        //调整高度
        node->height_ = MAX(getHeight(node->left_), getHeight(node->right_)) + 1;

        //左子树与右子树的高度差
        int subHeight = getHeight(node->left_) - getHeight(node->right_);
        //如果左边重
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
                //右单旋转
                rotateWithRight(node);
            }
            /*
                 A                   A                   C
               B         >>>>      C         >>>>     B     A  
                C                B
            */
            else if (subHeight < 0)
            {
                //左双旋转
                doubleRotateLeft(node);
            }
        }
        //如果左边重
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
                //左单旋转
                rotateWithLeft(node);
            }
            /*
            A                   A                       C
              B         >>>>      C         >>>>     A     B
             C                      B
            */
            else if (subHeight > 0)
            {
                //右双旋转
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
        //如果节点没有孩子
        if (node->left_ == nullptr&&node->right_ == nullptr)
        {
            //如果节点是根节点就直接删除
            if (node == root_)
            {
                delete node;
                return;
            }

            TreeNode *old = node;
            node = node->parent_;
            //如果节点是父节点的左孩子
            if (old == node->left_)
            {
                //将左孩子置空
                node->left_ = nullptr;
            }
            //如果节点是父节点的右孩子
            else
            {
                //将右孩子置空
                node->right_ = nullptr;
            }
            //如果节点是链表，清空链表
            TreeNode *linkNode = old->next_;
            while (linkNode != nullptr)
            {
                TreeNode *oldLink = linkNode;
                linkNode = linkNode->next_;
                delete oldLink;
            }
            //删除节点
            delete old;
            
        }
        //如果节点有孩子，先去左边
        else if (node->left_ != nullptr)
        {
            node = node->left_;
        }
        //再去右边
        else if (node->right_ != nullptr)
        {
            node = node->right_;
        }
    }
}

