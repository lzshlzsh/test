/**
 * @file test_unordered_map.cpp
 * @brief
 * @version 1.0
 * @date 03/04/2016 03:26:52 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */

#include <iostream>
#include <unordered_map>

using namespace std;

/**
 * @brief 
 * @class Key
 */
class Key
{
public:
    int i_, j_;
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    Key (int i, int j): i_(i), j_(j) {}
protected:
private:
};

/**
 * @brief 
 * @class KeyHash
 */
class KeyHash
{
public:
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    size_t operator() (const Key &key) const {
        return key.i_;
    }
protected:
private:
};

/**
 * @brief 
 * @class KeyEq
 */
class KeyEq
{
public:
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    bool operator() (const Key &a, const Key &b) const {
        return a.i_ == b.i_ && a.j_ == b.j_;
    }
protected:
private:
};

typedef std::unordered_map<Key, int, KeyHash, KeyEq> UnorderedMap;

/**
 * @brief 
 * @param[in]
 * @param[in,out]
 * @param[out]
 * @return 0 if success, < 0 otherwise
 */
int main() {
    UnorderedMap mymap;

    mymap.insert(std::make_pair(Key(1, 11), 21));
    mymap.insert(std::make_pair(Key(1, 12), 22));

    cout << mymap.size() << endl;

    return 0;
}

