#include <assert.h>
#include <sstream>
#include "qna_tool.h"
#include <fstream>
#include <string.h>
#include <algorithm>
#define INT_MAX 2147483647
using namespace std;

static int k0, k;
static char *b;
char temp[50];
char add_array[50];
static int parameter;

int cons(char a[], int i)
{
    switch (a[i])
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return 0;
    case 'y':
    {
        if (i == k0)
            return 1;
        else
            !cons(a, i - 1);
    }
    default:
        return 1;
    }
}

int m(char a[], int j, int k)
{
    int n = 0;
    int r = k0;
    int flag;
    int c = 0;
    int v = 0;
    int value1 = 0;
    int value2 = 0;
    int value = 0;
    int loop = 0;
    while (1)
    {

        while (r <= k)
        {
            {

                if (r > j)
                    break;
                if (!cons(a, r))
                {
                    c++;
                    value1 = 1;
                    break;
                }
                r++;
            }
            if (value1 == 1)
                break;
        }
        value1 = 0;
        r++;

        while (r <= k)
        {
            {

                if (r > j)
                    break;
                if (cons(a, r))
                {
                    v++;
                    value2 = 1;
                    break;
                }
                r++;
            }
            if (value2 == 1)
                break;
        }
        value2 = 0;
        r++;
        if ((c == v) && (r <= k + 1))
        {

            value = value + 1;
            c = 0;
            v = 0;
        }
        if (r > k)
            break;
    }

    return value;
}

int vowelinstem(char a[], int j)
{

    int last_w = j;
    int i;
    for (i = k0; i <= last_w; i++)
        if (!cons(a, i))
            return 1;
    return 0;
}

int doublec(char a[], int j)
{
    int last_w = j;
    if (j < k0 + 1)
        return 0;
    if (a[j] != a[j - 1])
        return 0;
    return cons(a, j);
}

int cvc(int i, char a[], int j)
{

    if (i <= k0 + 2)
    {
        if (!cons(a, i) || cons(a, i - 1) || !cons(a, i - 2))
        {
            int ch = a[i];
            if (ch == 'w' || ch == 'x' || ch == 'y')
                return 0;
        }
    }
    return 1;
}

void setto(int len_inc, char *add, char a[])
{
    int len3 = len_inc;
    if (parameter == 1)
    {
        char temp1[50];
        memset(temp1, 0, sizeof(temp1));
        memcpy(temp1, a, k + 1);
        memset(a, '\0', sizeof(a));
        strcpy(a, temp1);
        parameter = 0;
    }
    k += len_inc;
    strcat(a, add);
    char temp[50];
    memset(temp, 0, sizeof(temp));
    memcpy(temp, a, k + 1);
    memset(a, 0, sizeof(a));
    memcpy(a, temp, k + 1);
    return;
}

int ends(char a[], char *s, int length, int j)
{
    int last_w;
    int len = length;
    int pos = k - length + 1;
    char temp[50];
    memset(temp, 0, sizeof(temp));
    for (int m = 0; m <= len - 1; m++)
    {

        temp[m] = a[pos];
        pos++;
    }
    int r;
    if ((r = strcmp(s, temp)) == 0)
    {
        return 1;
    }
    else
        return 0;
}

void step1ab(char a[], int j)
{
    int last_w = j;
    int h = 0;
    if (a[k] == 's')
    {
        if (ends(a, "sses", 4, last_w) == 1)
        {
            k -= 2;
        }
        else if (ends(a, "ies", 3, last_w) == 1)
        {
            k -= 3;
            setto(1, "i", a);
        }
        else if (a[k - 1] != 's')
        {
            k--;
            return;
        }
    }
    else if (ends(a, "eed", 3, last_w) == 1)
    {
        if (m(a, last_w, k) > 1)
            k--;
    }
    else if ((ends(a, "ed", 2, last_w) == 1) || (ends(a, "ing", 3, last_w) == 1))
    {
        if ((ends(a, "ed", 2, last_w) == 1) && vowelinstem(a, last_w))
        {
            k -= 2;
        }
        if ((ends(a, "ing", 3, last_w) == 1) && vowelinstem(a, last_w))
        {
            k -= 3;
        }
        j = k;

        if (ends(a, "at", 2, j) == 1)
        {
            k -= 2;
            setto(3, "ate", a);
        }
        else if (ends(a, "bl", 2, j) == 1)
        {
            k -= 2;
            setto(3, "ble", a);
        }
        else if (ends(a, "iz", 2, j) == 1)
        {
            k -= 2;
            setto(3, "ize", a);
        }
        else if (doublec(a, k))
        {
            k--;
            {
                int ch = a[k];
                if (ch == 'l' || ch == 's' || ch == 'z')
                    k++;
            }
        }
    }
    if ((ends(a, "at", 2, j) == 1) && (ends(a, "bl", 2, j) == 1) && (ends(a, "iz", 2, j) == 1))
    {
        if (m(a, j, k) == 1 && cvc(k, a, 0))
        {
            parameter = 1;
            setto(1, "e", a);
        }
    }
    return;
}

void step1c(char a[])
{

    if (ends(a, "y", 1, k) && vowelinstem(a, k))
    {
        parameter = 1;
        k -= 1;
        setto(1, "i", a);
    }
}

void step2(char a[], int j)
{

    if ((m(a, j, k) > 0))
    {
        switch (a[k - 1])
        {

        case 'a':
            if (ends(a, "ational", 7, k))
            {
                k -= 7;
                parameter = 1;
                // cout << a << "The value is "
                //<< " " << k;
                setto(3, "ate", a);
                break;
            }
            if (ends(a, "tional", 6, k))
            {
                k -= 6;
                setto(4, "tion", a);
                break;
            }
            break;
        case 'c':
            if (ends(a, "enci", 4, k))
            {
                k -= 4;
                parameter = 1;
                setto(4, "ence", a);
                break;
            }
            else if (ends(a, "anci", 4, k))
            {
                k -= 4;
                parameter = 1;
                setto(4, "ance", a);
                break;
            }
            break;
        case 'e':
            if (ends(a, "izer", 4, k))
            {
                {
                    k -= 4;
                    parameter = 1;
                    setto(3, "ize", a);
                    break;
                }
            }
            break;
        case 'l':
            if (ends(a, "bli", 3, k))
            {
                k -= 3;
                parameter = 1;
                setto(3, "ble", a);
                break;
            }
            if (ends(a, "eli", 3, k))
            {
                k -= 3;
                setto(1, "e", a);
                break;
            }
            if (ends(a, "alli", 4, k))
            {
                k -= 4;
                parameter = 1;
                setto(2, "al", a);
                break;
            }
            if (ends(a, "entli", 5, k))
            {
                k -= 5;
                parameter = 1;
                setto(3, "ent", a);
                break;
            }
            if (ends(a, "ousli", 5, k))
            {
                k -= 5;
                parameter = 1;
                setto(3, "ous", a);
                break;
            }
            break;
        case 'o':
            if (ends(a, "ator", 4, k))
            {
                k -= 4;
                parameter = 1;
                setto(3, "ate", a);
                break;
            }
            if (ends(a, "ization", 7, k))
            {
                k -= 7;
                parameter = 1;
                setto(3, "ize", a);
                break;
            }
            if (ends(a, "ation", 5, k))
            {
                k -= 5;
                parameter = 1;
                setto(3, "ate", a);
                break;
            }
            break;
        case 's':
            if (ends(a, "alism", 5, k))
            {
                k -= 5;
                parameter = 1;
                setto(2, "al", a);
                break;
            }
            if (ends(a, "iveness", 7, k))
            {
                k -= 7;
                parameter = 1;
                setto(3, "ive", a);
                break;
            }
            if (ends(a, "fulness", 7, k))
            {
                k -= 7;
                parameter = 1;
                setto(3, "ful", a);
                break;
            }
            if (ends(a, "ousness", 7, k))
            {
                k -= 7;
                parameter = 1;
                setto(3, "ous", a);
                break;
            }
            break;
        case 't':
            if (ends(a, "aliti", 5, k))
            {
                k -= 5;
                parameter = 1;
                setto(2, "al", a);
                break;
            }
            if (ends(a, "iviti", 5, k))
            {
                k -= 5;
                parameter = 1;
                setto(3, "ive", a);
                break;
            }
            if (ends(a, "biliti", 6, k))
            {
                k -= 6;
                parameter = 1;
                setto(3, "ble", a);
                break;
            }
            break;
        case 'g':
            if (ends(a, "logi", 4, k))
            {
                k -= 4;
                parameter = 1;
                setto(3, "log", a);
                break;
            }
        }
    }
}

void step3(char a[], int j)
{
    if (m(a, j, k) > 0)
    {
        switch (a[k])
        {

        case 'e':
            if (ends(a, "icate", 5, k))
            {
                k -= 5;
                parameter = 1;
                setto(2, "ic", a);
                break;
            }
            if (ends(a, "ative", 5, k))
            {
                k -= 5;
                parameter = 1;
                setto(0, " ", a);
                break;
            }
            if (ends(a, "alize", 5, k))
            {
                k -= 5;
                parameter = 1;
                setto(2, "al", a);
                break;
            }
            break;
        case 'i':
            if (ends(a, "iciti", 5, k))
            {
                k -= 5;
                parameter = 1;
                setto(2, "ic", a);
                break;
            }
            break;
        case 'l':
            if (ends(a, "ical", 4, k))
            {
                k -= 4;
                parameter = 1;
                setto(2, "ic", a);
                break;
            }
            if (ends(a, "ful", 3, k))
            {
                k -= 3;
                parameter = 1;
                setto(0, " ", a);
                break;
            }
            break;
        case 's':
            if (ends(a, "ness", 4, k))
            {
                k -= 4;
                parameter = 1;
                setto(0, "", a);
                break;
            }
            break;
        }
    }
}

void step4(char a[], int j)
{
    if ((m(a, j, k) > 1))
    {
        switch (a[k - 1])
        {
        case 'a':
            if (ends(a, "al", 2, k))
            {
                k -= 2;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
        case 'c':
            if (ends(a, "ance", 4, k))
            {
                k -= 4;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
            if (ends(a, "ence", 4, k))
            {
                k -= 4;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
        case 'e':
            if (ends(a, "er", 2, k))
            {
                k -= 2;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
        case 'i':
            if (ends(a, "ic", 2, k))
            {
                k -= 2;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
        case 'l':
            if (ends(a, "able", 4, k))
            {
                k -= 4;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
            if (ends(a, "ible", 4, k))
            {
                k -= 4;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
        case 'n':
            if (ends(a, "ant", 3, k))
            {
                k -= 3;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
            if (ends(a, "ement", 5, k))
            {
                k -= 5;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
            if (ends(a, "ment", 4, k))
            {
                k -= 4;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
            if (ends(a, "ent", 3, k))
            {
                k -= 3;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
        case 'o':
            if (ends(a, "ion", 3, k) && (a[k - 3] == 's' || a[k - 3] == 't'))
            {
                k -= 3;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
            if (ends(a, "ou", 2, k))
            {
                k -= 2;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
        case 's':
            if (ends(a, "ism", 3, k))
            {
                k -= 3;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
        case 't':
            if (ends(a, "ate", 3, k))
            {
                k -= 3;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
            if (ends(a, "iti", 3, k))
            {
                k -= 3;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
        case 'u':
            if (ends(a, "ous", 3, k))
            {
                k -= 3;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
        case 'v':
            if (ends(a, "ive", 3, k))
            {
                k -= 3;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
        case 'z':
            if (ends(a, "ize", 3, k))
            {
                k -= 3;
                parameter = 1;
                setto(0, " ", a);
                return;
            }
        default:
            return;
        }
        if (m(a, j, k) > 1)
            j = k;
    }
}

void step5(char a[], int j)
{
    j = k;
    if (a[k] == 'e')
    {
        int x = m(a, j, k);
        if (x > 1)
        {
            k--;
        }
        else if ((x == 1) && !cvc(k - 1, a, 0))
            k--;
    }
    if (m(a, j, k) > 1)
    {
        if (doublec(a, k))
        {
            if (a[k] == 'l')
                k--;
        }
    }
}

int stem(char a[], int i, int j)
{
    k = j;
    k0 = i;
    if (k <= k0 + 1)
        return k;
    step1ab(a, j);
    step1c(a);
    step2(a, j);
    step3(a, j);
    step4(a, j);
    step5(a, j);

    return k;
}

string convert_to_stem(string word)
{
    char *a = new char[50];
    std::stringstream is(word);
    while (is.good())
    {
        memset(a, '\0', sizeof(a));
        while (is.getline(a, 50, '\n'))
        {
            memset(temp, '\0', sizeof(temp));
            memcpy(temp, a, strlen(a));
            memset(a, 0, sizeof(a));
            strcpy(a, temp);
            a[strlen(a)] = '\0';
            for (int j = 0; j < strlen(a); ++j)
            {
                if (a[j] == '*' || a[j] == '!' || a[j] == '@' || a[j] == '#' || a[j] == '$' || a[j] == '%' || a[j] == '^' || a[j] == '&' || a[j] == '(' || a[j] == ')' || a[j] == '{' || a[j] == '[' || a[j] == '}' || a[j] == '.' || a[j] == '/' || a[j] == '>' || a[j] == '<' || a[j] == ',' || a[j] == ':' || a[j] == ';')
                    a[j] = tolower(a[j]);
            }
            int iCount = -1;
            iCount = strlen(a);
            --iCount;
            a[stem(a, 0, iCount) + 1] = 0;
            return a;
        }
    }
    // return a;
}

long long stringToLongLong(const std::string &str)
{
    long long result = 0;
    int sign = 1;
    size_t i = 0;
    while (i < str.length() && (str[i] == ' ' || str[i] == '\t'))
    {
        i++;
    }
    if (i < str.length() && (str[i] == '-' || str[i] == '+'))
    {
        sign = (str[i++] == '-') ? -1 : 1;
    }
    while (i < str.length() && isdigit(str[i]))
    {
        result = result * 10 + (str[i++] - '0');
    }
    return result * sign;
}
HeapNode::HeapNode()
{
    par = NULL;
    left = NULL;
    right = NULL;
}

HeapNode::HeapNode(double _score, int _book_code, int _page, int _paragraph, int _sentence_no)
{
    val = _score;
    book_code = _book_code;
    page = _page;
    paragraph = _paragraph;
    sentence_no = _sentence_no;
}

HeapNode::~HeapNode()
{
}

MinHeap::MinHeap()
{
    size = 0;
    root = NULL;
}

int bitl(int num)
{
    int count = 0;
    while (num != 0)
    {
        num = num / 2;
        count++;
    }
    return count;
}

void heapify_up(HeapNode *node)
{
    while (node->par != NULL && node->val < node->par->val)
    {
        double temp = node->val;
        int temp1 = node->book_code;
        int temp2 = node->page;
        int temp3 = node->paragraph;
        int temp4 = node->sentence_no;
        node->val = node->par->val;
        node->book_code = node->par->book_code;
        node->page = node->par->page;
        node->paragraph = node->par->paragraph;
        node->sentence_no = node->par->sentence_no;
        node->par->val = temp;
        node->par->book_code = temp1;
        node->par->page = temp2;
        node->par->paragraph = temp3;
        node->par->sentence_no = temp4;
        node = node->par;
    }
}

void heapify_down(HeapNode *node)
{
    while (node->left != NULL)
    {
        HeapNode *temp = node->left;
        if (node->right != NULL and node->left->val > node->right->val)
        {
            temp = node->right;
        }
        if (temp->val >= node->val)
        {
            break;
        }
        double x = node->val;
        int t1 = node->book_code;
        int t2 = node->page;
        int t3 = node->paragraph;
        int t4 = node->sentence_no;
        node->val = temp->val;
        node->book_code = temp->book_code;
        node->page = temp->page;
        node->paragraph = temp->paragraph;
        node->sentence_no = temp->sentence_no;
        temp->val = x;
        temp->book_code = t1;
        temp->page = t2;
        temp->paragraph = t3;
        temp->sentence_no = t4;
        node = temp;
    }
}

HeapNode *find(HeapNode *node, int size)
{
    int depth = bitl(size + 1);
    HeapNode *parent = node;
    if (depth >= 3)
    {
        for (int i = depth - 2; i >= 1; i--)
        {
            if (((size + 1) >> i) & 1)
            {
                parent = parent->right;
            }
            else
            {
                parent = parent->left;
            }
        }
    }
    return parent;
}

Node *MinHeap::return_top(int k)
{
    if (size > k)
    {
        while (size > k)
        {
            pop();
        }
    }
    Node *root = NULL;
    Node *current = NULL;
    while (size > 0)
    {
        Node *a = get_min();
        pop();
        if (root == NULL)
        {
            root = a;
            current = a;
        }
        else
        {
            current->left = a;
            a->right = current;
            current = a;
            root = current;
        }
    }

    return root;
}

void MinHeap::push_heap(double num, int _book_code, int _page, int _paragraph, int _sentence_no, int k)
{

    if (size == k)
    {
        if (root->val < num)
        {
            pop();
        }
        else
        {
            return;
        }
    }
    HeapNode *node = new HeapNode(num, _book_code, _page, _paragraph, _sentence_no);
    if (root == NULL)
    {
        root = node;
        size++;
        return;
    }
    else
    {
        HeapNode *parent = find(root, size);
        if (parent->left == NULL)
        {
            parent->left = node;
        }
        else
        {
            parent->right = node;
        }
        node->par = parent;
        heapify_up(node);
    }
    size++;
    return;
}

Node *MinHeap::get_min()
{
    if (root == NULL)
    {
        return NULL;
    }
    Node *a = new Node(root->book_code, root->page, root->paragraph, root->sentence_no, root->val);
    a->left = nullptr;
    a->right = nullptr;
    return a;
}

void MinHeap::pop()
{
    if (root == NULL)
    {
        return;
    }
    HeapNode *Parent = find(root, size - 1);
    if (size == 1)
    {
        size--;
        delete root;
        root = NULL;
        return;
    }
    HeapNode *x = Parent->right;
    if (x == NULL)
    {
        x = Parent->left;
    }
    if (x->par)
    {
        if (x == x->par->left)
        {
            x->par->left = NULL;
        }
        else
        {
            x->par->right = NULL;
        }
    }
    x->par = NULL;
    root->val = x->val;
    root->book_code = x->book_code;
    root->page = x->page;
    root->paragraph = x->paragraph;
    root->sentence_no = x->sentence_no;
    delete x;
    x = NULL;
    size--;
    heapify_down(root);
}

void delete_heap(HeapNode *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->left)
    {
        delete_heap(node->left);
    }
    if (node->right)
    {
        delete_heap(node->right);
    }
    if (node->par)
    {
        if (node->par->right == node)
        {
            node->par->right = NULL;
        }
        else
        {
            node->par->left = NULL;
        }
        node->par = NULL;
    }
    delete node;
}

MinHeap::~MinHeap()
{
    delete_heap(root);
    root = NULL;
}

TrieNode ::TrieNode()
{
    for (int i = 0; i <= 53; i++)
    {
        child[i] = nullptr;
    }
    freq_count = 0;
}

TrieNode ::~TrieNode()
{
    for (int i = 0; i < 54; i++)
    {
        if (child[i] != nullptr)
        {
            delete child[i];
        }
    }
}

TrieNode_1 ::TrieNode_1()
{
    for (int i = 0; i <= 53; i++)
    {
        child_1[i] = nullptr;
    }
    freq_count_1 = 0;
}
TrieNode_1 ::~TrieNode_1()
{
    for (int i = 0; i < 54; i++)
    {
        if (child_1[i] != nullptr)
        {
            delete child_1[i];
        }
    }
}

Duo::Duo()
{
    s = "";
    f = 0;
    query_freq = 0;
}
Duo::Duo(string s, int freq, int q_freq)
{
    this->s = s;
    f = freq;
    query_freq = q_freq;
}

ParaNode::ParaNode()
{
}

ParaNode::ParaNode(int b, int pg, int para)
{
    book_id = b;
    page = pg;
    paragraph = para;
}

int gindex(char c)
{
    if (c >= 97 and c <= 122)
    {
        return c - 97;
    }
    else if (c >= 48 and c <= 57)
    {
        return c - 22;
    }
    else if (c >= 35 and c <= 38)
    {
        return c + 1;
    }
    else if (c == 42)
    {
        return 40;
    }
    else if (c == 43)
    {
        return 41;
    }
    else if (c == 47)
    {
        return 42;
    }
    else if (c == 60 || c == 61 || c == 62)
    {
        return c - 17;
    }
    else if (c == 92)
    {
        return 46;
    }
    else if (c == 94 || c == 95 || c == 96)
    {
        return c - 47;
    }
    else if (c == 123 || c == 124 || c == 125 || c == 126)
    {
        return c - 73;
    }
    return -1;
}

char gchar(int index)
{
    if (index >= 0 && index <= 25)
    {
        return static_cast<char>(index + 97);
    }
    else if (index >= 26 && index <= 35)
    {
        return static_cast<char>(index + 22);
    }
    else if (index >= 36 && index <= 39)
    {
        return static_cast<char>(index - 1);
    }
    else if (index == 40)
    {
        return '*';
    }
    else if (index == 41)
    {
        return '+';
    }
    else if (index == 42)
    {
        return '/';
    }
    else if (index >= 43 && index <= 45)
    {
        return static_cast<char>(index + 17);
    }
    else if (index == 46)
    {
        return '\\';
    }
    else if (index >= 47 && index <= 49)
    {
        return static_cast<char>(index + 47);
    }
    else if (index >= 50 && index <= 53)
    {
        return static_cast<char>(index + 73);
    }
    return ' ';
}

Trie::Trie()
{
    root = new TrieNode();
    size = 0;
}
Trie ::~Trie()
{
    delete root;
}

void Trie::Insert_update_freq(int book_code, int page, int paragraph, string word)
{
    if (size == 0)
    {
        root = new TrieNode();
        size++;
    }
    TrieNode *curr = root;
    if (word != "")
    {
        for (int i = 0; i < word.length(); i++)
        {
            int index = gindex(word[i]);
            if (curr->child[index] == nullptr)
            {
                curr->child[index] = new TrieNode();
            }
            curr = curr->child[index];
        }
        curr->freq_count = curr->freq_count + 1;
        ParaNode p(book_code, page, paragraph);
        if (curr->adj_para.empty() == true)
        {
            curr->adj_para.push_back(p);
            return;
        }
        if (curr->adj_para.back().book_id != book_code or curr->adj_para.back().page != page or curr->adj_para.back().paragraph != paragraph)
        {
            curr->adj_para.push_back(p);
            return;
        }
    }
}

int Trie::Find_score(string word)
{
    TrieNode *curr = root;
    for (int i = 0; i < word.length(); i++)
    {
        int index = gindex(word[i]);
        if (curr->child[index] == nullptr)
        {
            return 0;
        }
        curr = curr->child[index];
    }
    return curr->freq_count;
}

Trie_1::Trie_1()
{
    root_1 = new TrieNode_1();
    size_1 = 0;
}
Trie_1 ::~Trie_1()
{
    delete root_1;
}

void Trie_1::Insert_update_freq_1(string word, long long freq)
{
    if (size_1 == 0)
    {
        root_1 = new TrieNode_1();
        size_1++;
    }
    TrieNode_1 *curr = root_1;
    if (word != "")
    {
        for (int i = 0; i < word.length(); i++)
        {
            int index = gindex(word[i]);
            if (curr->child_1[index] == nullptr)
            {
                curr->child_1[index] = new TrieNode_1();
            }
            curr = curr->child_1[index];
        }
        curr->freq_count_1 = freq;
    }
}

long long Trie_1::Find_score_1(string word)
{
    TrieNode_1 *curr = root_1;
    for (int i = 0; i < word.length(); i++)
    {
        int index = gindex(word[i]);
        if (curr->child_1[index] == nullptr)
        {
            return 0;
        }
        curr = curr->child_1[index];
    }
    return curr->freq_count_1;
}

vector<ParaNode> Trie::get_para_arr_helper(string word)
{
    TrieNode *curr = root;
    for (int i = 0; i < word.length(); i++)
    {
        int index = gindex(word[i]);
        if (curr->child[index] == nullptr)
        {
            vector<ParaNode> v;
            return v;
        }
        curr = curr->child[index];
    }
    return curr->adj_para;
}

bool is_separator(char c)
{
    bool b = (c == '.' || c == ',' || c == '-' || c == ':' || c == '!' || c == '\"' || c == '\'' || c == '(' || c == ')' || c == '?' || c == '[' || c == ']' || c == ' ' || c == ';' || c == '@');
    return b;
}
void preprocess_sent(string &sent)
{
    for (auto &z : sent)
    {
        if (z >= 'A' and z <= 'Z')
        {
            z += 32;
        }
        else if (is_separator(z))
        {
            z = ' ';
        }
    }
}
void preprocess_sent_2(string &sent)
{
    for (auto &z : sent)
    {
        if (z >= 'A' and z <= 'Z')
        {
            z += 32;
        }
        else if (!isalnum(z))
        {
            z = ' ';
        }
    }
}
QNA_tool::QNA_tool()
{
    int bookCodes = 98;
    int pages = 580;
    int paragraphs = 90;
    corpus = vector<vector<vector<string>>>(bookCodes, vector<vector<string>>(pages, vector<string>(paragraphs, "")));
    corpus_p2 = vector<vector<vector<string>>>(bookCodes, vector<vector<string>>(pages, vector<string>(paragraphs, "")));
    Read_from_csv();
    Read_from_csv_2();
}

void QNA_tool::preprocess_helper(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    preprocess_sent(sentence);
    stringstream ss(sentence);
    string word;
    string s = corpus[book_code - 1][page][paragraph];
    s = s + sentence + " ";
    corpus[book_code - 1][page][paragraph] = s;
    while (ss >> word)
    {
        if (word != "")
        {
            t->Insert_update_freq(book_code, page, paragraph, word);
        }
    }
}

void QNA_tool::preprocess_helper_2(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    preprocess_sent_2(sentence);
    stringstream ss(sentence);
    string word;
    string s = corpus_p2[book_code - 1][page][paragraph];
    while (ss >> word)
    {
        if (word != "")
        { // cout<<word<<endl;
            word = convert_to_stem(word);
            s = s + word + " ";
            t_p2->Insert_update_freq(book_code, page, paragraph, word);
        }
    }
    corpus_p2[book_code - 1][page][paragraph] = s;
}

int find(string word, vector<Duo> question)
{
    for (int j = 0; j < question.size(); j++)
    {
        if (question[j].s == word)
        {
            return j;
        }
    }
    return -1;
}

QNA_tool::~QNA_tool()
{
    delete d_ideal;
    d_ideal = nullptr;
    delete t;
    t = nullptr;
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    preprocess_helper(book_code, page, paragraph, sentence_no, sentence);
    return;
}

void QNA_tool::insert_sentence_2(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    preprocess_helper_2(book_code, page, paragraph, sentence_no, sentence);
    return;
}

void convert(string question, vector<Duo> &res)
{
    stringstream ss(question);
    string wor;
    while (ss >> wor)
    {
        if (find(wor, res) == -1)
        {
            Duo d(wor, 0, 1);
            res.push_back(d);
        }
        else
        {
            int k = find(wor, res);
            res[k].query_freq++;
        }
    }
}

void convert_2(string question, vector<Duo> &res, Trie_1 *d_ideal_2)
{
    stringstream ss(question);
    string wor;
    while (ss >> wor)
    {
        if (d_ideal_2->Find_score_1(wor) == 0)
        {
            if (find(wor, res) == -1)
            { // cout<<wor;
                wor = convert_to_stem(wor);
                // cout<<wor<<endl;
                Duo d(wor, 0, 1);
                res.push_back(d);
            }
            else
            {
                int k = find(wor, res);
                res[k].query_freq++;
            }
        }
    }
}
struct mycmp
{
    bool operator()(Duo &d1, Duo &d2)
    {
        return d1.f < d2.f;
    }
};

void Critical_word_finder(vector<Duo> &result, vector<string> &cw)
{
    int min = INT_MAX;
    sort(result.begin(), result.end(), mycmp());
    cout << result[0].s << endl;
    string min_st;
    min_st = result[0].s;
    cw.push_back(min_st);
    int n = result.size();
    result[0].query_freq = n; // name is query freq but is priority
    for (int i = 1; i < n; i++)
    {
        if (result[i].f < 1140)
        {
            cw.push_back(result[i].s);
        }
        result[i].query_freq = n - i;
    }
}

void fillLPS(string s, vector<int> &lps)
{
    lps[0] = 0;
    int i = 1;
    int M = s.length();
    int len = 0;
    while (i < M)
    {
        if (s[i] == s[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
            else
            {
                len = lps[len - 1];
            }
        }
    }
}

bool KMP(const string &pattern, string sentence, int &n_matches)
{
    int N = sentence.length();
    int M = pattern.length();
    vector<int> lps(N);
    fillLPS(pattern, lps);
    bool b = false;
    int i = 0, j = 0;
    while (i < N)
    {
        if (pattern[j] == sentence[i])
        {
            i++;
            j++;
        }
        if (j == M)
        {
            n_matches++;
            j = lps[j - 1];
            b = true;
        }
        else if (i < N and pattern[j] != sentence[i])
        {
            if (j == 0)
                i++;
            else
                j = lps[j - 1];
        }
    }
    return b;
}

Node *QNA_tool::get_top_k_para_2(string question, int k)
{
    preprocess_sent_2(question);
    int bookCodes = 98;
    int pages = 580;
    int paragraphs = 90;
    marked_corpus_p2 = vector<vector<vector<int>>>(bookCodes, vector<vector<int>>(pages, vector<int>(paragraphs, -1)));
    MinHeap m_2;
    vector<Duo> result = {};
    convert_2(question, result, d_ideal_2);
    for (auto z : result)
    {
        int idx = find(z.s, result);
        int freq = t_p2->Find_score(z.s);
        result[idx].f = freq;
        cout << z.s << freq << endl;
    }
    vector<string> crit_word;
    Critical_word_finder(result, crit_word);
    for (auto p : crit_word)
    { // cout<<p;
        vector<ParaNode> adj_p = t_p2->get_para_arr_helper(p);
        for (auto q : adj_p)
        {
            double Score_para = 0;
            if (marked_corpus_p2[q.book_id - 1][q.page][q.paragraph] == -1)
            {
                string para = corpus_p2[q.book_id - 1][q.page][q.paragraph];
                for (auto internal_word : result)
                {
                    int freq_wor = 0;
                    if (KMP(internal_word.s, para, freq_wor))
                    {                                                               // actually priority not query freq
                        Score_para += (internal_word.query_freq * 1000 + freq_wor); // since frequency can this weight as max words in paragraph is 1140//we give priority simultaneos presence of query word than individual freq;
                    }
                }
                marked_corpus_p2[q.book_id - 1][q.page][q.paragraph] = 1;
                m_2.push_heap(Score_para, q.book_id, q.page, q.paragraph, 0, k);
            }
        }
    }
    marked_corpus_p2.clear();
    return m_2.return_top(k);
}

Node *QNA_tool::get_top_k_para(string question, int k)
{
    preprocess_sent(question);
    int bookCodes = 98;
    int pages = 580;
    int paragraphs = 90;
    marked_corpus = vector<vector<vector<int>>>(bookCodes, vector<vector<int>>(pages, vector<int>(paragraphs, -1)));
    stringstream ss(question);
    string word;
    string internal_word;
    MinHeap m;
    vector<Duo> result = {};
    convert(question, result);
    while (ss >> word)
    {
        if (word != "" and t->Find_score(word) != -1)
        {
            vector<ParaNode> adj_p = t->get_para_arr_helper(word);
            for (ParaNode p : adj_p)
            {
                double Score_para = 0;
                if (marked_corpus[p.book_id - 1][p.page][p.paragraph] == -1)
                {
                    stringstream int_ss(corpus[p.book_id - 1][p.page][p.paragraph]);
                    string word_1;
                    while (int_ss >> word_1)
                    {
                        int k = find(word_1, result);
                        if (k != -1)
                        {
                            result[k].f += 1;
                        }
                    }
                    for (int h = 0; h < result.size(); h++)
                    {
                        int k = (t->Find_score(result[h].s) + 1);
                        double j = (static_cast<double>(k) / static_cast<double>((d_ideal->Find_score_1(result[h].s) + 1)));
                        Score_para += j * (result[h].f) * (result[h].query_freq);
                        result[h].f = 0;
                    }
                    marked_corpus[p.book_id - 1][p.page][p.paragraph] = 1;
                    // ofstream out;
                    // out.open("hi.txt", ios::app);
                    // out << p.book_id << " " << p.page << " " << p.paragraph << " " << Score_para << endl;
                    // out.close();
                    m.push_heap(Score_para, p.book_id, p.page, p.paragraph, 0, k);
                }
            }
        }
    }
    marked_corpus.clear();
    return m.return_top(k);
}

void QNA_tool::Read_from_csv()
{
    std::ifstream file("unigram_freq.csv");
    if (!file.is_open())
    {
        std::cout << "Error in opening file" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string str1, str2;
        if (std::getline(iss, str1, ',') && std::getline(iss, str2, ','))
        {
            if (str2 != "count")
            {
                long long c = stringToLongLong(str2);
                d_ideal->Insert_update_freq_1(str1, c);
            }
        }
    }
    file.close();
}

void QNA_tool::Read_from_csv_2()
{
    std::ifstream file("our_unigram_freq.csv");
    if (!file.is_open())
    {
        std::cout << "Error in opening file" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string str1, str2;
        if (std::getline(iss, str1, ',') && std::getline(iss, str2, ','))
        {
            if (str2 != "count")
            {
                str1 = convert_to_stem(str1);
                long long c = stringToLongLong(str2);
                d_ideal_2->Insert_update_freq_1(str1, c);
            }
        }
    }
    file.close();
}

void QNA_tool::query(string question, string filename)
{
    Node *n = get_top_k_para_2(question, 5);
    query_llm(filename, n, 4, "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", question);
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph)
{

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence))
    {
        tuple += ')';
        int metadata[5];
        std::istringstream iss(tuple);
        std::string token;
        iss.ignore(1);
        int idx = 0;
        while (std::getline(iss, token, ','))
        {
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos)
            {
                token = token.substr(start, end - start + 1);
            }
            if (token[0] == '\'')
            {
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            }
            else
            {
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if (
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph))
        {
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node *root, int k, string API_KEY, string question)
{
    Node *traverse = root;
    int num_paragraph = 0;
    string sg = "";
    while (num_paragraph < k)
    {
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        sg += p_file + " ";
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    outfile.close();
    string command = "python3 ";
    command += filename;
    command += " ";
    command += "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";
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";
    system(command.c_str());
    return;
}