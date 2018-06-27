#include <string>
#include <unordered_map>

using namespace std;

class TrieNode
{
public:
	wchar_t c = L'\0';
	unordered_map<wchar_t, TrieNode*> children;
	bool isLeaf = false;

	TrieNode();

	TrieNode(wchar_t c);
};


class Trie
{
private:
	TrieNode *root;

public:
	virtual ~Trie()
	{
		delete root;
	}

	Trie();



	// Inserts a word into the trie.
	virtual void insert(const wstring &word);



       // Returns if the word is in the trie.
	virtual bool search(const wstring &word);


	// Returns if there is any word in the trie
	that starts with the given prefix.
	virtual bool startsWith(const wstring &prefix);


	virtual TrieNode *searchNode(const wstring &str);};




TrieNode::TrieNode(wchar_t c)
{
	this->c = c;
}

Trie::Trie()
{
	root = new TrieNode();
}

void Trie::insert(const wstring &word)
{
	unordered_map<wchar_t, TrieNode*> &children = root->children;

	for (int i = 0; i < word.length(); i++)
	{
		wchar_t c = word[i];

		TrieNode *t;
		if (children.find(c) != children.end())
		{
				t = children[c];
		}
		else
		{
			t = new TrieNode(c);
			children.emplace(c, t);
		}

		children = t->children;

		//set leaf node
		if (i == word.length() - 1)
		{
			t->isLeaf = true;
		}
	}
}

bool Trie::search(const wstring &word)
{
	TrieNode *t = searchNode(word);

	if (t != nullptr && t->isLeaf)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Trie::startsWith(const wstring &prefix)
{
	if (searchNode(prefix) == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

TrieNode *Trie::searchNode(const wstring &str)
{
	unordered_map<wchar_t, TrieNode*> &children = root->children;
	TrieNode *t = nullptr;
	for (int i = 0; i < str.length(); i++)
	{
		wchar_t c = str[i];
		if (children.find(c) != children.end())
		{
			t = children[c];
			children = t->children;
		}
		else
		{
			return nullptr;
		}
	}

	return t;
}
