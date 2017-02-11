#include "BoxelChunkMesh.hpp"

template<unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ>
class BoxelChunk
{
public:
    typedef BoxelChunk<sizeX, sizeY, sizeZ> Self;
    typedef BoxelChunkGrid<sizeX, sizeY, sizeZ> MyGrid;
    
    void generateGrid(){
        for(unsigned int y(0); y<MyGrid::SIZE_Y; ++y){
            for(unsigned int z(0); z<MyGrid::SIZE_Z; ++z){
                for(unsigned int x(0); x<MyGrid::SIZE_X; ++x){
                    if(x+5>y){
                        if(y==MyGrid::SIZE_Y-1){
                            mGrid.at(x, y, z) = BoxelType::GRASS;
                        }else if(y>MyGrid::SIZE_X/2){
                            mGrid.at(x, y, z) = BoxelType::DIRT;
                        }else{
                            mGrid.at(x, y, z) = BoxelType::STONE;
                        }
                    }else{
                        mGrid.at(x, y, z) = BoxelType::AIR;
                    }
                }
            }
        }
    }
    
    void generateMesh(){
        BoxelChunkMesh<MyGrid> voxMeshStone(mGrid, BoxelType::STONE);
        mModelStone = Renderer::createModel(
              voxMeshStone.getVerticesSize(),
               voxMeshStone.getPositions(),
               voxMeshStone.getTexCoord(),
               voxMeshStone.getNormal(),
               voxMeshStone.getIndexSize()/3,
               voxMeshStone.getFaces(),
               mMaterialStone
                                           );
        
        BoxelChunkMesh<MyGrid> voxMeshDirt(mGrid, BoxelType::DIRT);
        mModelDirt = Renderer::createModel(
               voxMeshDirt.getVerticesSize(),
               voxMeshDirt.getPositions(),
               voxMeshDirt.getTexCoord(),
               voxMeshDirt.getNormal(),
               voxMeshDirt.getIndexSize()/3,
               voxMeshDirt.getFaces(),
               mMaterialDirt
                                          );
        
        BoxelChunkMesh<MyGrid> voxMeshGrass(mGrid, BoxelType::GRASS);
        mModelGrass = Renderer::createModel(
               voxMeshGrass.getVerticesSize(),
               voxMeshGrass.getPositions(),
               voxMeshGrass.getTexCoord(),
               voxMeshGrass.getNormal(),
               voxMeshGrass.getIndexSize()/3,
               voxMeshGrass.getFaces(),
               mMaterialGrass
                                           );
        
        mObjectStone = Renderer::createObject(mModelStone);
        mObjectDirt = Renderer::createObject(mModelDirt);
        mObjectGrass = Renderer::createObject(mModelGrass);
    }
    
    void loadTexture(){
        mTextureStone  = Renderer::createTexture("../data/stone.dds");
        mTextureDirt  = Renderer::createTexture("../data/dirt.dds");
        mTextureGrass = Renderer::createTexture( "../data/grass.dds");
        
        mMaterialStone = Renderer::createMaterial(mTextureStone);
        mMaterialDirt = Renderer::createMaterial(mTextureDirt);
        mMaterialGrass = Renderer::createMaterial(mTextureGrass);
    }
    
    void draw(){
        Renderer::renderObject(mObjectStone);
        Renderer::renderObject(mObjectDirt);
        Renderer::renderObject(mObjectGrass);
    }
    
    void unload(){
        Renderer::destoryModel(mModelStone);
        Renderer::destoryModel(mModelDirt);
        Renderer::destoryModel(mModelGrass);
        
        Renderer::destroyObject(mObjectStone);
        Renderer::destroyObject(mObjectDirt);
        Renderer::destroyObject(mObjectGrass);
        
        Renderer::destroyTexture(mTextureStone);
        Renderer::destroyTexture(mTextureDirt);
        Renderer::destroyTexture(mTextureGrass);
        
        Renderer::destroyMaterial(mMaterialStone);
        Renderer::destroyMaterial(mMaterialDirt);
        Renderer::destroyMaterial(mMaterialGrass);
    }
    
private:
    MyGrid mGrid;
    
    Renderer::Model_handle mModelStone;
    Renderer::Model_handle mModelDirt;
    Renderer::Model_handle mModelGrass;
    
    Renderer::Object_handle mObjectStone;
    Renderer::Object_handle mObjectDirt;
    Renderer::Object_handle mObjectGrass;
    
    Renderer::Texture_handle mTextureStone;
    Renderer::Texture_handle mTextureDirt;
    Renderer::Texture_handle mTextureGrass;
    
    Renderer::Material_handle mMaterialStone;
    Renderer::Material_handle mMaterialDirt;
    Renderer::Material_handle mMaterialGrass;
};
 
