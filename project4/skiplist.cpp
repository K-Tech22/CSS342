#include "skiplist.h"
#include "random.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

using namespace std;

ostream &operator<<(ostream &out, const SkipList &skip)
{

    SNode *curr = skip.head;
    int level = skip.levels;
    while (level != 0)
    {
        out << "[level: " << level << "] ";
        curr = curr->next[level];
        while (curr != nullptr)
        {
            out << curr->val << "-->";
            curr = curr->next[level];
        }
        curr = skip.head;
        out << "nullptr\n";
        --level;
    }
    return out;
}

// Copy constructor for skiplist
SkipList::SkipList(const SkipList &other)
{

    // New head
    this->head = new SNode(other.head->val);
    // Same levels
    this->levels = other.levels;
    // Same probability
    this->probability = other.probability;

    // Looping through all levels
    for (int i = 1; i <= levels; i++)
    {
        // Curr is the SNode after head at each level
        SNode *curr = other.head->next[i];
        // Tail is the head
        SNode *tail = this->head;
        while (curr != nullptr)
        {
            // New SNode is created for each SNode from other
            tail->next[i] = new SNode(curr->val);
            curr = curr->next[i];
            tail = tail->next[i];
        }
        // Making curr to head for next level
        curr = other.head->next[i];
    }
}
// Constructor for SNode that takes a val
SNode::SNode(int val)
{
    this->val = val;
    next.push_back(nullptr);
    next.push_back(nullptr);
    next.push_back(nullptr);
}
// Copy Constructor for SNode that takes levels & probability
SkipList::SkipList(int levels, int probability)
    : levels{levels}, probability{probability}
{
    assert(levels > 0 && probability >= 0 && probability < 100);
    this->head = new SNode(INT_MIN);
}

// Destructor
SkipList::~SkipList()
{
    while (head->next[0] != nullptr)
    {
        SNode *sNode = head;
        head = head->next[0];
        delete sNode;
    }
}

// checks if the value needs to be inserted at a higher level
bool SkipList::shouldInsertAtHigherLevel() const
{
    return probability >= Random::random() % 100;
}

// Gets all the SNodes before a particular value
vector<SNode *> SkipList::getBeforeNodes(int val) const
{
    // Initializing a vector
    vector<SNode *> result;
    SNode *prev = nullptr;
    SNode *curr = head;
    // Going through all the levels starting from last
    for (int i = levels; i >= 0; i--)
    {
        while (curr != nullptr && curr->val < val)
        {
            prev = curr;
            curr = curr->next[i];
        }
        // prev is inserted to result when the nested while loop ends
        result.push_back(prev);
        // If prev is not equal to NULL
        if (prev != NULL)
        {
            // Prev is assigned to curr SNode
            curr = prev;
        }
    }
    // Reversing the vector so that level 1 SNodes appear first
    reverse(result.begin(), result.end());
    return result;
}

// Returns true if val is in SkipList, otherwise returns false
bool SkipList::contains(int val) const
{

    // Looping through each level
    for (int i = levels; i >= 0; i--)
    {
        SNode *curr = head->next[i];
        while (curr != nullptr)
        {
            // if SNode is found, returns true
            if (curr->val == val)
            {
                return true;
            }
            curr = curr->next[i];
        }
    }

    return false;
}
// Returns true if the value is removed successfully
// Returns false if the value is not present
bool SkipList::remove(int val)
{

    bool removed = false;
    int level = levels - 1;
    vector<SNode *> prevNodes = getBeforeNodes(val);

    // SNode that will be deleted
    SNode *goodByeNode = prevNodes[0]->next[0];

    while (level > 0)
    {
        // if prevNodes is not nullptr and its next SNode's val == val
        if (prevNodes[level]->next[level] != nullptr &&
            prevNodes[level]->next[level]->val == val)
        {
            // SNode is omitted and next is pointing to next next
            prevNodes[level]->next[level] =
                prevNodes[level]->next[level]->next[level];
            removed = true;
        }
        level--;
    }
    delete goodByeNode;
    return removed;
}

// Prompts for a vector of values to be added to the SkipList
void SkipList::add(const vector<int> &values)
{
    // Each item of the vector is called to add
    for (int i : values)
    {
        add(i);
    }
}

// Adds SNode with the value to SkipList and keeps it sorted
void SkipList::add(int val)
{

    // Making a new SNode
    SNode *newNode = new SNode();
    // Assigning the value
    newNode->val = val;
    // Currently at level 1
    int level = 1;
    // Getting previous SNodes before the val
    vector<SNode *> prevNodes = getBeforeNodes(val);

    // Checks if there is a SNode present after head
    if (head->next[level] == nullptr)
    {
        // SNode is inserted as the first SNode
        head->next[level] = newNode;

        // Checks if val is less than the first SNode
    }
    else if (val < head->next[level]->val)
    {
        // If it is, then SNode comes before the first SNode
        newNode->next[1] = head->next[1];
        head->next[1] = newNode;
    }
    else
    {
        // If other SNodes present, it gets inserted in sorted order
        // with respect to SNodes present before
        newNode->next[level] = prevNodes[1]->next[level];
        prevNodes[1]->next[level] = newNode;
    }
    // Incrementing level
    level++;

    while (level <= levels && shouldInsertAtHigherLevel())
    {

        // Checks if level has no SNodes present
        if (head->next[level] == nullptr)
        {
            // SNode is inserted as the first SNode of the level
            head->next[level] = newNode;
            // Incrementing level
            level++;

            // If other SNodes present
        }
        else
        {
            // If no before SNodes present
            if (prevNodes[level] == nullptr)
            {
                // SNode is inserted
                newNode->next[level] = head->next[level];
                head->next[level] = newNode;

                // If there are SNodes present in the vector
            }
            else
            {
                // SNode is inserted
                newNode->next[level] = prevNodes[level]->next[level];
                prevNodes[level]->next[level] = newNode;
            }
            // Incrementing level
            level++;
        }
    }
}
