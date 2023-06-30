#pragma once
#include <vector>

#include "Vector3D.h"

namespace Hyrule
{
	namespace Physics
	{
		/// <summary>
		/// ���� �������� ���� ���Ҹ��� ���� ����Ʈ��
		/// ���뼺�� �Ű澲���� ���� ����
		/// </summary>
		// template <typename Data, size_t DepthLimit>
		class Octree
		{
		public:

			struct Data
			{
			public:
				// �ݶ��̴� �߽����κ��� ���� �� ������ ���̸� �ѱ���
				Data(Vector3D* _data, const Vector3D& _centre, float _halfLength) : 
					data(_data), 
					min(_centre.x - _halfLength, _centre.y - _halfLength, _centre.z - _halfLength),
					max(_centre.x + _halfLength, _centre.y + _halfLength, _centre.z + _halfLength)
				{}
				~Data() {}

			public:
				bool operator== (const Vector3D* _rawData) noexcept
				{
					return data == _rawData;
				}

				Vector3D* data;				// ������
				Vector3D min;				// �������� ����
				Vector3D max;
			};

			struct Node
			{
			public:
				Node() noexcept = delete;
				Node(const Vector3D& _centre, float _halfLength, size_t _depth) :
					min(_centre.x - _halfLength, _centre.y - _halfLength, _centre.z - _halfLength), 
					max(_centre.x + _halfLength, _centre.y + _halfLength, _centre.z + _halfLength),
					depth(_depth), child(), dataList()
				{}
				~Node() noexcept {}

			private:
				const size_t depth;				// ���� ����
				Vector3D min;					// ��尡 �Ҵ���� ����
				Vector3D max;
				Node* child[8];					// �ڽ� ���
				std::vector<Data*> dataList;

			public:
				// ���� ����� ������ ����
				size_t GetCount()
				{
					return dataList.size();
				}

				// �ݶ��̴� üũ�� ���ؼ� ��ȯ�ϴ� ����.
				std::vector<Data*> GetDataList()
				{
					return dataList;
				}

				void AddData(Node* _node, Data* _data, size_t _depth)
				{
					// AABB �� üũ�ϰ� AddData�� ȣ���ϱ� ������
					// ���� ���� ������ �����ϸ� �ٷ� �迭�� �ִ´�.
					dataList.push_back(_data);

					if (depth == 0)
					{
						return;
					}

					for (size_t i = 0; i < 8; ++i)
					{
						Vector3D tempCenter;
						Vector3D tempLength;
						this->GetChildCenter(i, tempCenter, tempLength);
						if (AABB(tempCenter - tempLength, tempCenter + tempLength, _data))
						{
							child[i] = new Node(tempCenter, ((max.x - min.x) * 0.25f), _depth - 1);
							child[i]->AddData(child[i], _data, _depth - 1);
						}
					}
				}

				void RemoveData(Data* _data)
				{
					// ���� ��忡�� �����͸� ����
					auto a = dataList.erase(remove(dataList.begin(), dataList.end(), _data));
					
					// ������ �ڽ� ��嵵 Ȯ�� ����.
					if (a == dataList.end())
					{
						return;
					}

					// for������ �ڽ� ��忡 ������ ���� �Լ��� ȣ��
					// ��� ���鼭 �ڽ� ����� �����͸� ����
					for (auto& e : child)
					{
						e->RemoveData(_data);
					}
				}

				void GetChildCenter(size_t _id, Vector3D& _outCenter, Vector3D& _outLength)
				{
					Vector3D center = (max + min) * 0.5f;
					Vector3D length = (max - min) * 0.25f;

					// 3���� �迭�� �����ϰ�
					// ��Ʈ ��������
					if (_id & 1)
					{
						length.x *= -1.f;
					}
					if (_id & 2)
					{
						length.z *= -1.f;
					}
					if (_id & 4)
					{
						length.y *= -1.f;
					}

					_outCenter = center - length;
					_outLength = length;
				}

				bool AABB(const Vector3D& _childMin, const Vector3D& _childMax, Data* _data) const
				{
					// ���� ���� AABB üũ��.
					return 
						_data->max.x >= _childMin.x && _data->min.x <= _childMax.x &&
						_data->max.y >= _childMin.y && _data->min.y <= _childMax.y &&
						_data->max.z >= _childMin.z && _data->min.z <= _childMax.z;
				}
			};


		public:
			Octree() noexcept = default;
			Octree(const Vector3D& _centre, float _length, size_t _limit = 4) : depthLimit(_limit), root()
			{
				root = new Node(_centre, _length, _limit);
			}
			~Octree() noexcept = default;

		private:
			const size_t depthLimit;
			Node* root;
		
		public:
			void Insert(Data* _data)
			{
				// root�� AABB�� Data�� AABB�� ���ϰ� ���� �ȿ� ������ ����.
				// 
				root->AddData(root, _data, depthLimit);
			}

			void RemoveData(Data* _data)
			{
				root->RemoveData(_data);
				// root ��忡 ������ ������ ��û
				// root ���� �ݺ����� ���鼭 �ڽ� ����� ������ ���� �Լ��� ȣ��
				// ��ͷ� �ڽ� ����� ������ ������ ȣ����.
			}
		};
	}
}


/*
������ �߽ɰ� ũ�⸦ �⺻ ���������� ����
min, max ���� �����ʹ� �߽ɰ� ũ��� ä���־��� ���� 

�������� �����Ϳ�, �������� �߽ɰ� ũ�⸦ �޾Ƽ� �������� ���Ǹ� ������

Insert�� �ϸ� �켱 
*/