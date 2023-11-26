#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
#include "dict.h"
#include "search.h"

using namespace std;

class HeapNode{
  public:
  double val;
  HeapNode* par = NULL;
  HeapNode* left = NULL;
  HeapNode* right = NULL;
  int book_code,page,paragraph,sentence_no;
  HeapNode();
  HeapNode(double _score,int _book_code, int _page, int _paragraph, int _sentence_no);
  ~HeapNode();
};

class MinHeap{
  public:
  int size = 0;
  HeapNode* root = NULL;
  int capacity;
  public:
  MinHeap();
  ~MinHeap();
  Node *return_top(int k);
  void push_heap(double num,int _book_code, int _page, int _paragraph, int _sentence_no,int k);
  Node  *get_min();
  void pop();
};

class ParaNode{
    public:
    int book_id;
    int page;
    int paragraph;
    ParaNode();
    ParaNode(int b,int pg,int para);
   // ~ParaNode();
};

class TrieNode{
    public:
    TrieNode* child[54];
    int freq_count;
    vector<ParaNode>adj_para;
    TrieNode();
    ~TrieNode();

};

class Trie{
    public:
    TrieNode* root;
    int size=0;
    Trie();
    void Insert_update_freq(int book_code, int page, int paragraph,string word);
    int Find_score(string word);
    vector<ParaNode> get_para_arr_helper(string word);
   ~Trie();
};

class TrieNode_1{
    public:
    TrieNode_1* child_1[54];
    long long freq_count_1;
    TrieNode_1();
    ~TrieNode_1();
};

class Trie_1{
    public:
    TrieNode_1* root_1;
    int size_1=0;
    Trie_1();
    void Insert_update_freq_1(string word,long long freq);
    long long Find_score_1(string word);
    ~Trie_1();
};

// class TrieNode_2{
//     public:
//     TrieNode_2* child_2[54];
//     long long freq_count_2;
//     TrieNode_2();
//     //~TrieNode_1();
// };

// class Trie_2{
//     public:
//     TrieNode_2* root_2;
//     int size_2=0;
//     Trie_2();
//     void Insert_update_freq_2(string word);
//     int Find_score_2(string word);
//    // ~Trie_1();
// };
class Duo{
    public:
    string s;
    int f;
    int query_freq;
    Duo();
    Duo(string s,int freq,int q_freq);
};
class QNA_tool {
private:
    void query_llm(string filename, Node* root, int k, string API_KEY, string question);
    Trie_1* d_ideal=new Trie_1();
    Trie_1* d_ideal_2=new Trie_1();
    vector<vector<vector<string>>>corpus;
    vector<vector<vector<string>>>corpus_p2;
    vector<vector<vector<int>>>marked_corpus;
    vector<vector<vector<int>>>marked_corpus_p2;
    Trie* t= new Trie();  
    Trie* t_p2=new Trie(); 
public:
    QNA_tool(); 
    ~QNA_tool();
    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    void insert_sentence_2(int book_code, int page, int paragraph, int sentence_no, string sentence);
    Node* get_top_k_para(string question, int k);
    Node* get_top_k_para_2(string question, int k);
    std::string get_paragraph(int book_code, int page, int paragraph);
    void query(string question, string filename);
    void Read_from_csv();
    void Read_from_csv_2();
    void preprocess_helper(int book_code, int page, int paragraph, int sentence_no,string sentence); 
    void preprocess_helper_2(int book_code, int page, int paragraph, int sentence_no,string sentence); 
};