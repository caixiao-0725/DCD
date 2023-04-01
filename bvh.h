#pragma once

#include "aabb.h"
#include "model.h"

class BVHIndexPair
{
public:

    BVHIndexPair(const unsigned int& id1, const unsigned int& id2);

    /**
     * @brief Get the Tri Pair object
     *
     * @param[out]   id1 records one of the triangleID
     * @param[out]   id2 another one
     */
    void getTriPair(unsigned int* id1, unsigned int* id2) const;

    /**
     * @brief Makesure the smaller one is in m_id[0], and the larger one is in m_id[1]
     */
    void sort();

    /**
     * @brief Compare two TriPair object, the smaller one should contain smaller triID
     *
     * @param[in] other the TriPair object needs to be compared
     * @return  Compare result
     */
    bool operator<(const BVHIndexPair& other) const;

private:
    /**
     * @brief contains a pair of the triangleID
     */
    unsigned int m_id[2];
};


class bvh_node {
	aabb  _box;

	unsigned int _id;
	bvh_node *_left;
	bvh_node *_right;

public:
	bvh_node();
	bvh_node(unsigned int);
	bvh_node(unsigned int *, unsigned int, Model *);

	~bvh_node();
	void collide(bvh_node *, std::vector<BVHIndexPair>* f);

friend class bvh_tree;
};

class bvh_tree {
	bvh_node	*_root;

public:
	bvh_tree(Model *);
	~bvh_tree();

	void collide(bvh_tree *,std::vector<BVHIndexPair>*);
};

void getTriangle(Model* model,
    const unsigned int tri_id,
    vec3d& p0,
    vec3d& p1,
    vec3d& p2);