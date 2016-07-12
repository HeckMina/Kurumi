#include "FBXImporter.h"

#include "fbxsdk.h"

#pragma comment(lib,"libfbxsdk-md.lib")

namespace Kurumi
{
	void DumpNode(FbxNode*node)
	{
		printf("node : %s\n", node->GetName());
		int nAttributeCount = node->GetNodeAttributeCount();
		for (int i=0;i<nAttributeCount;++i)
		{
			auto attriNode = node->GetNodeAttributeByIndex(i);
			if (attriNode!=nullptr)
			{
				if (attriNode->GetAttributeType()==FbxNodeAttribute::eMesh)
				{
					printf("detect a mesh attribute node\n");
					FbxMesh*mesh = node->GetMesh();
					int nVertexCount = mesh->GetControlPointsCount();
					printf("vertex count is : %d",nVertexCount);
					int nPolygonCount = mesh->GetPolygonCount();
					for (int nIndex=0;nIndex<nPolygonCount;++nIndex)
					{
						printf("polygon %d : index count %d\n", nIndex, mesh->GetPolygonSize(nIndex));
					}
				}
			}
		}
		int nChildCount = node->GetChildCount();
		for (int i=0;i<nChildCount;i++)
		{
			DumpNode(node->GetChild(i));
		}
	}

	void FBXImporter::Test()
	{
		FbxManager*fbxManager = FbxManager::Create();
		FbxIOSettings*fbxIOSetting = FbxIOSettings::Create(fbxManager, IOSROOT);
		FbxImporter*fbxImporter = FbxImporter::Create(fbxManager, "");

		fbxManager->SetIOSettings(fbxIOSetting);

		fbxImporter->Initialize("media/model/cube.fbx", -1, fbxManager->GetIOSettings());

		FbxScene*scene = FbxScene::Create(fbxManager, "CubeScene");
		fbxImporter->Import(scene);
		fbxImporter->Destroy();

		FbxNode*rootNode = scene->GetRootNode();
		DumpNode(rootNode);
		fbxManager->Destroy();
	}
}