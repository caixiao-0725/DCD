#include <stdlib.h>
#include <assert.h>

#include "bvh.h"
#include "origin.h"
#include "Model.h"
#include "aap.h"


#define IsLeaf(node) ((node->_left == NULL)&&(node->_right==NULL))


BVHIndexPair::BVHIndexPair(const unsigned int& id1, const unsigned int& id2)
{
	m_id[0] = id1;
	m_id[1] = id2;
}

void BVHIndexPair::getTriPair(unsigned int* id1, unsigned int* id2) const
{
	*id1 = m_id[0];
	*id2 = m_id[1];
}

void BVHIndexPair::sort()
{
	if (m_id[0] > m_id[1])
	{
		std::swap(m_id[0], m_id[1]);
	}
}

bool BVHIndexPair::operator<(const BVHIndexPair& other) const
{
	if (m_id[0] == other.m_id[0])
	{
		return m_id[1] < other.m_id[1];
	}
	else
	{
		return m_id[0] < other.m_id[0];
	}
}



bvh_tree::bvh_tree(Model *mdl)
{
	aabb total;
	for (unsigned int i=0; i<mdl->verts_.size(); i++)
		total += mdl->verts_[i];

	mdl->_tri_boxes = new aabb[mdl->faces_.size()];
	mdl->_tri_centers = new vec3d[mdl->faces_.size()];

	aap  pln(total);
	unsigned int *idx_buffer = new unsigned int[mdl->faces_.size()];
	unsigned int left_idx = 0, right_idx = mdl->faces_.size();

	for (unsigned int i=0; i<mdl->faces_.size(); i++) {
		vec3d &p1 = mdl->verts_[mdl->faces_[i].x];
		vec3d &p2 = mdl->verts_[mdl->faces_[i].y];
		vec3d &p3 = mdl->verts_[mdl->faces_[i].z];

		mdl->_tri_centers[i].x = aap::middle_xyz(0, p1, p2, p3);
		mdl->_tri_centers[i].y = aap::middle_xyz(1, p1, p2, p3);
		mdl->_tri_centers[i].z = aap::middle_xyz(2, p1, p2, p3);

		if (pln.inside(mdl->_tri_centers[i]))
			idx_buffer[left_idx++] = i;
		else
			idx_buffer[--right_idx] = i;

		mdl->_tri_boxes[i] += p1;
		mdl->_tri_boxes[i] += p2;
		mdl->_tri_boxes[i] += p3;
	}

	_root = new bvh_node();
	_root->_box = total;
	_root->_left = new bvh_node(idx_buffer, left_idx, mdl);
	_root->_right = new bvh_node(idx_buffer+left_idx, mdl->faces_.size()-left_idx, mdl);

	delete [] mdl->_tri_boxes;
	delete [] mdl->_tri_centers;
	mdl->_tri_boxes = NULL;
	mdl->_tri_centers = NULL;
	delete [] idx_buffer;
}

bvh_tree::~bvh_tree()
{
	delete _root;
}

//#################################################################

bvh_node::bvh_node()
{
	_id = UINT_MAX;
	_left = _right = NULL;
}

bvh_node::~bvh_node()
{
	if (_left) delete _left;
	if (_right) delete _right;
}

bvh_node::bvh_node(unsigned int id)
{
	_left = _right = NULL;
	_id = id;
}

bvh_node::bvh_node(unsigned int *lst, unsigned int lst_num, Model *mdl)
{
	assert(lst_num > 0);
	_left = _right = NULL;
	_id = UINT_MAX;
	
	if (lst_num == 1) {
		_id = lst[0];
		_box = mdl->_tri_boxes[_id];
	}
	else { // try to split them
		for (unsigned int t=0; t<lst_num; t++) {
			int i=lst[t];
			_box += mdl->_tri_boxes[i];
		}

		if (lst_num == 2) { // must split it!
			_left = new bvh_node(lst[0]);
			_right = new bvh_node(lst[1]);
		} else {
			aap pln(_box);
			unsigned int left_idx = 0, right_idx = lst_num-1;

			for (unsigned int t=0; t<lst_num; t++) {
				int i=lst[left_idx];
				if (pln.inside(mdl->_tri_centers[i]))
					left_idx++;
				else {// swap it
					unsigned int tmp = i;
					lst[left_idx] = lst[right_idx];
					lst[right_idx--] = tmp;
				}
			}

			int hal = lst_num/2;
			if (left_idx == 0 || left_idx == lst_num)
			{
				_left = new bvh_node(lst, hal, mdl);
				_right = new bvh_node(lst+hal, lst_num-hal, mdl);
			}
			else {
				_left = new bvh_node(lst, left_idx, mdl);
				_right = new bvh_node(lst+left_idx, lst_num-left_idx, mdl);
			}

		}
	}
}


void
bvh_tree::collide(bvh_tree* other, std::vector<BVHIndexPair>* f)
{
	if (f->size() != 0) {
		f->clear();
	}
	if (other)
	{
		_root->collide(other->_root, f);
	}

}


void
bvh_node::collide(bvh_node* other, std::vector<BVHIndexPair>* f)
{
	assert(other);
	if (!_box.overlaps(other->_box)) {
		return;
	}

	if (IsLeaf(this) && IsLeaf(other)) {
		BVHIndexPair new_pair = BVHIndexPair(_id, other->_id);
		f->push_back(new_pair);
		return;
	}

	if (IsLeaf(this)) {
		collide(other->_left, f);
		collide(other->_right, f);
	}
	else {
		_left->collide(other, f);
		_right->collide(other, f);
	}
}

void getTriangle(Model* model,
				 const unsigned int tri_id,
				 vec3d& p0,
				 vec3d& p1,
				 vec3d& p2)
{
	p0 = model->verts_[model->faces_[tri_id].x];
	p1 = model->verts_[model->faces_[tri_id].y];
	p2 = model->verts_[model->faces_[tri_id].z];
}