#include"Terrain.h"





// 生成密度函数
std::vector<geo_pos> generateDensityFunction(int n) {
    std::vector<geo_pos> test;
    int flag=1;
    for(int i=0;i<16;i++)
        for(int j=0;j<16;j++)
            for(int k=0;k<3;k++)
            {
                geo_pos temp;
                if(n==-1&&i!=0&&j!=0){
                   flag=-1;
                    
                temp.x=i*0.1f*flag;
                temp.y=k*0.1f;
                temp.z=j*0.1f*flag;
                }else{        
                temp.x=i*0.1f;
                temp.y=k*0.1f;
                temp.z=j*0.1f;}
                test.push_back(temp);
            }
    return test;
}
std::vector<Block> generateTerrain(int n){
    std::vector<geo_pos>test =generateDensityFunction(n) ;
    std::vector<Block> terrain;
    Block temp;
    glm::mat4 model(1.0f);
    for(int i=0;i<test.size();i++)
    {
        temp.ID=1;
        temp.model=glm::translate(model,glm::vec3(test[i].x,test[i].y,test[i].z));
        terrain.push_back(temp);
    }
    return terrain;
}