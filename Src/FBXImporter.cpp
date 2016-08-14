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
					int nTriangleCount = mesh->GetPolygonCount();
					for (int nIndex=0;nIndex<nTriangleCount;++nIndex)
					{
						printf("triangle %d : index count %d\n", nIndex, mesh->GetPolygonSize(nIndex));
					}
					int nLayerCount = mesh->GetLayerCount();
					for (int nLayerIndex=0;nLayerIndex<nLayerCount;++nLayerIndex)
					{
						//normal,uv,texture,tangent
						FbxLayer*layer = mesh->GetLayer(nLayerIndex);
						if (layer)
						{
							//FbxLayerElementNormal*normalLayer = (FbxLayerElementNormal*)layer->GetLayerElementOfType(FbxLayerElement::eNormal);//
							FbxLayerElementNormal*normalLayer = layer->GetNormals();
							if (normalLayer)
							{
								switch (normalLayer->GetReferenceMode())
								{
								case FbxLayerElement::EReferenceMode::eDirect:
								{
									auto&directArray = normalLayer->GetDirectArray();
									float x=directArray.GetAt(0).mData[0];
									float y = directArray.GetAt(0).mData[1];
									float z = directArray.GetAt(0).mData[2];
									printf("eDirect ,array count %d\n",directArray.GetCount());
								}
									break;
								case FbxLayerElement::EReferenceMode::eIndexToDirect:
								{
									auto&directArray = normalLayer->GetDirectArray();
									auto&indexArray = normalLayer->GetIndexArray();
									int nRealIndex = indexArray.GetAt(0);
									float x = directArray.GetAt(nRealIndex).mData[0];
									float y = directArray.GetAt(nRealIndex).mData[1];
									float z = directArray.GetAt(nRealIndex).mData[2];
									printf("eIndexToDirect ,array count %d\n", indexArray.GetCount());
								}
									break;
								case FbxLayerElement::EReferenceMode::eIndex:
									break;
								}
							}
						}
					}
				}
			}
			int materialCount = node->GetMaterialCount();
			printf("material count : %d\n",materialCount);
			for (int j=0;j<materialCount;++j)
			{
				FbxSurfaceMaterial*mat = node->GetMaterial(j);
				//material:lambert¡¢phong¡¢cg
				if (mat->GetClassId()==FbxSurfaceLambert::ClassId)
				{
					printf("lambert material\n");
				}
				else if (mat->GetClassId()==FbxSurfacePhong::ClassId)
				{
					FbxProperty prop = mat->FindProperty(FbxSurfaceMaterial::sDiffuse);
					printf("%d phong material %s\n", j,mat->GetName());
					if (prop.IsValid())
					{
						int textureCount = prop.GetSrcObjectCount(FbxTexture::ClassId);
						FbxTexture*texture = prop.GetSrcObject<FbxTexture>();
						if (texture)
						{
							printf("material diffuse texture name %s texture count %d\n", texture->GetName(), textureCount);
						}
					}
				}
				else
				{
					//cg ...
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

		fbxImporter->Initialize("media/model/tauren.fbx", -1, fbxManager->GetIOSettings());

		FbxScene*scene = FbxScene::Create(fbxManager, "CubeScene");
		fbxImporter->Import(scene);
		fbxImporter->Destroy();

		FbxNode*rootNode = scene->GetRootNode();
		DumpNode(rootNode);
		fbxManager->Destroy();
	}
}