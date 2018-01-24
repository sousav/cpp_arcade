//
// GLObjectData.cpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sat Apr  1 02:30:56 2017 Sousa Victor
// Last update Sat Apr  8 21:57:35 2017 Sousa Victor
//

#include "GLObjectData.hpp"

GLObjectData::GLObjectData()
{
    this->_scene = NULL;
    this->_scene_list = 0;
    this->_angle = 0.f;
    this->_textureIds = NULL;
    this->_posX = 0;
    this->_posY = 0;
    this->_posZ = 0;
    this->_scaleX = 1;
    this->_scaleY = 1;
    this->_scaleZ = 1;
    this->_rotX = 0;
    this->_rotY = 0;
    this->_rotZ = 0;
    this->_offX = 0;
    this->_offY = 0;
    this->_offZ = 0;
}

GLObjectData::GLObjectData(std::string const & filename)
{
    this->_scene = NULL;
    this->_scene_list = 0;
    this->_angle = 0.f;
    this->_textureIds = NULL;
    this->_posX = 0;
    this->_posY = 0;
    this->_posZ = 0;
    this->_scaleX = 1;
    this->_scaleY = 1;
    this->_scaleZ = 1;
    this->_rotX = 0;
    this->_rotY = 0;
    this->_rotZ = 0;
    this->_offX = 0;
    this->_offY = 0;
    this->_offZ = 0;
    loadasset(filename.data());
    if (this->_scene == NULL) {
        std::cout << "loading failed" << std::endl;
    }

}

GLObjectData::~GLObjectData() {

}

GLObjectData &GLObjectData::operator=(const GLObjectData &obj) {
    this->_scene = obj._scene;
    this->_scene_list = obj._scene_list;
    this->_angle = obj._angle;
    this->_textureIds = obj._textureIds;
    this->_posX = obj._posX;
    this->_posY = obj._posY;
    this->_posZ = obj._posZ;
    this->_scaleX = obj._scaleX;
    this->_scaleY = obj._scaleY;
    this->_scaleZ = obj._scaleZ;
    this->_rotX = obj._rotX;
    this->_rotY = obj._rotY;
    this->_rotZ = obj._rotZ;
    this->_offX = obj._offX;
    this->_offY = obj._offY;
    this->_offZ = obj._offZ;
    this->_scene_min = obj._scene_min;
    this->_scene_max = obj._scene_max;
    this->_scene_center = obj._scene_center;
    this->_textureIdMap = obj._textureIdMap;
    this->_textureIds = obj._textureIds;
    return *this;
}

GLObjectData::GLObjectData(GLObjectData const &obj) {
    this->_scene = obj._scene;
    this->_scene_list = obj._scene_list;
    this->_angle = obj._angle;
    this->_textureIds = obj._textureIds;
    this->_posX = obj._posX;
    this->_posY = obj._posY;
    this->_posZ = obj._posZ;
    this->_scaleX = obj._scaleX;
    this->_scaleY = obj._scaleY;
    this->_scaleZ = obj._scaleZ;
    this->_rotX = obj._rotX;
    this->_rotY = obj._rotY;
    this->_rotZ = obj._rotZ;
    this->_offX = obj._offX;
    this->_offY = obj._offY;
    this->_offZ = obj._offZ;
    this->_scene_min = obj._scene_min;
    this->_scene_max = obj._scene_max;
    this->_scene_center = obj._scene_center;
    this->_textureIdMap = obj._textureIdMap;
    this->_textureIds = obj._textureIds;
}

void GLObjectData::get_bounding_box_for_node(const aiNode* nd, aiVector3D* min, aiVector3D* max, aiMatrix4x4* trafo) const {
	aiMatrix4x4 prev;
	unsigned int n = 0, t;

	prev = *trafo;
	aiMultiplyMatrix4(trafo,&nd->mTransformation);

	for (; n < nd->mNumMeshes; ++n) {
		const aiMesh* mesh = this->_scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t) {

			aiVector3D tmp = mesh->mVertices[t];
			aiTransformVecByMatrix4(&tmp,trafo);

			min->x = aisgl_min(min->x,tmp.x);
			min->y = aisgl_min(min->y,tmp.y);
			min->z = aisgl_min(min->z,tmp.z);

			max->x = aisgl_max(max->x,tmp.x);
			max->y = aisgl_max(max->y,tmp.y);
			max->z = aisgl_max(max->z,tmp.z);
		}
	}

	for (n = 0; n < nd->mNumChildren; ++n) {
		get_bounding_box_for_node(nd->mChildren[n],min,max,trafo);
	}
	*trafo = prev;
}

void GLObjectData::get_bounding_box (aiVector3D* min, aiVector3D* max) const
{
	aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);

	min->x = min->y = min->z =  1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(this->_scene->mRootNode,min,max,&trafo);
}

int GLObjectData::loadasset(const char* path)
{
    this->_scene = aiImportFile(path,aiProcessPreset_TargetRealtime_MaxQuality);

	if (this->_scene) {
		get_bounding_box(&this->_scene_min,&this->_scene_max);
		this->_scene_center.x = (this->_scene_min.x + this->_scene_max.x) / 2.0f;
		this->_scene_center.y = (this->_scene_min.y + this->_scene_max.y) / 2.0f;
		this->_scene_center.z = (this->_scene_min.z + this->_scene_max.z) / 2.0f;
        if (!loadGLTextures(_scene, path))
            return 1;
		return 0;
	}
    return 1;
}

void GLObjectData::move(float x, float y, float z) {
    this->_posX = x;
    this->_posY = y;
    this->_posZ = z;
}

void GLObjectData::scale(float x, float y, float z) {
    this->_scaleX = x;
    this->_scaleY = y;
    this->_scaleZ = z;
}

void GLObjectData::rotate(float x, float y, float z) {
    this->_rotX = x;
    this->_rotY = y;
    this->_rotZ = z;
}

void GLObjectData::setOffset(float x, float y, float z) {
    this->_offX = x;
    this->_offY = y;
    this->_offZ = z;
}

void GLObjectData::draw() {
    if (_scene == NULL)
        return;
    glEnable(GL_NORMALIZE);
    glPushMatrix();

    glTranslatef(this->_posX + this->_offX,
                 this->_posY + this->_offY,
                 this->_posZ + this->_offZ);
    glRotatef(this->_rotX, 1, 0, 0);
    glRotatef(this->_rotY, 0, 1, 0);
    glRotatef(this->_rotZ, 0, 0, 1);
    glScalef(this->_scaleX, this->_scaleY, this->_scaleZ);

    recursive_render(this->_scene, this->_scene->mRootNode);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_NORMALIZE);
    glDisable(GL_CULL_FACE);
}

void GLObjectData::color4_to_float4(const aiColor4D *c, float f[4]) const
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

void GLObjectData::set_float4(float f[4], float a, float b, float c, float d) const
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

void GLObjectData::apply_material(const aiMaterial *mtl)
{
    float c[4];

	GLenum fill_mode;
	int ret1, ret2;
	aiColor4D diffuse;
	aiColor4D specular;
	aiColor4D ambient;
	aiColor4D emission;
	float shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;	// changed: to unsigned

	int texIndex = 0;
	aiString texPath;	//contains filename of texture

	if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
	{
		//bind texture
        glEnable(GL_TEXTURE_2D);
		unsigned int texId = *_textureIdMap[texPath.data];
		glBindTexture(GL_TEXTURE_2D, texId);
	}


	set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	max = 1;
	ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
	if((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}
void GLObjectData::recursive_render (const aiScene *sc, const aiNode* nd) {
	unsigned int i;
	unsigned int n=0, t;

	// update transform
	glPushMatrix();

	// draw all meshes assigned to this node
	for (n = 0; n < nd->mNumMeshes; ++n)
	{

		const aiMesh* mesh = _scene->mMeshes[nd->mMeshes[n]];

		apply_material(sc->mMaterials[mesh->mMaterialIndex]);

		if(mesh->mNormals == NULL)
		{
			glDisable(GL_LIGHTING);
		}
		else
		{
			glEnable(GL_LIGHTING);
		}

		if(mesh->mColors[0] != NULL)
		{
			glEnable(GL_COLOR_MATERIAL);
		}
		else
		{
			glDisable(GL_COLOR_MATERIAL);
		}

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch(face->mNumIndices)
			{
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);

			for(i = 0; i < face->mNumIndices; i++)		// go through all vertices in face
			{
				int vertexIndex = face->mIndices[i];	// get group index for current index
				if(mesh->mColors[0] != NULL)
					glColor4f(mesh->mColors[0][vertexIndex].r, mesh->mColors[0][vertexIndex].g, mesh->mColors[0][vertexIndex].b, mesh->mColors[0][vertexIndex].a);
				if(mesh->mNormals == NULL)
                    break;
				if(mesh->HasTextureCoords(0))		//HasTextureCoords(texture_coordinates_set)
				{
					glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y); //mTextureCoords[channel][vertex]
				}

				glNormal3fv(&mesh->mNormals[vertexIndex].x);
				glVertex3fv(&mesh->mVertices[vertexIndex].x);
			}
			glEnd();
		}
	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n)
	{
		recursive_render(sc, nd->mChildren[n]);
	}

	glPopMatrix();
}

std::string GLObjectData::getBasePath(const std::string& path) {
	size_t pos = path.find_last_of("\\/");
	return (std::string::npos == pos) ? "" : path.substr(0, pos + 1);
}
int GLObjectData::loadGLTextures(const aiScene* _scene, std::string const & path) {
	ILboolean success;

	// Before calling ilInit() version should be checked.
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		/// wrong DevIL version ///
		std::string err_msg = "Wrong DevIL version";
		std::cout << err_msg << std::endl;
		return 0;
	}

	ilInit(); // Initialization of DevIL

	if (_scene->HasTextures())
        return 0;

	// getTexture Filenames and Numb of Textures
	for (unsigned int m=0; m<_scene->mNumMaterials; m++)
	{
		int texIndex = 0;
		aiReturn texFound = AI_SUCCESS;

		aiString path;	// filename

		while ((texFound = _scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path)) == AI_SUCCESS)
		{
			_textureIdMap[path.data] = NULL; //fill map with textures, pointers still NULL yet
			texIndex++;
		}
	}

	int numTextures = _textureIdMap.size();

	// array with DevIL image IDs
	ILuint* imageIds = NULL;
	imageIds = new ILuint[numTextures];

	// generate DevIL Image IDs
	ilGenImages(numTextures, imageIds); // Generation of numTextures image names

	// create and fill array with GL texture ids
	_textureIds = new GLuint[numTextures];
	glGenTextures(numTextures, _textureIds); // Texture name generation

	// get iterator
	std::map<std::string, GLuint*>::iterator itr = _textureIdMap.begin();

	std::string basepath = getBasePath(path);
	for (int i=0; i<numTextures; i++)
	{

		//save IL image ID
		std::string filename = (*itr).first;  // get filename
		(*itr).second =  &_textureIds[i];	  // save texture id for filename in map
		itr++;								  // next texture


		ilBindImage(imageIds[i]); // Binding of DevIL image name
        std::replace(filename.begin(), filename.end(), '\\', '/');
		std::string fileloc = basepath + filename;	///Loading of image
        std::cout << "loading: " << fileloc << " = ";
		success = ilLoadImage(fileloc.c_str());

		if (success) //If no error occurred:
		{
            // Convert every colour component into unsigned byte.If your image contains
            // alpha channel you can replace IL_RGB with IL_RGBA
            success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
			if (!success)
			{
				// Error occurred
                std::cout << "KO" << std::endl;
				std::cout << "Couldn't convert image" << std::endl;
				return 0;
			}
            // Binding of texture name
            glBindTexture(GL_TEXTURE_2D, _textureIds[i]);
			// redefine standard texture values
            // We will use linear interpolation for magnification filter
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            // We will use linear interpolation for minifying filter
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            // Texture specification
            glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
				ilGetData());
            // we also want to be able to deal with odd texture dimensions
            glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
            glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
            glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );
            glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );
            std::cout << "OK" << std::endl;
		}
		else
		{
            std::cout << "KO" << std::endl;
			std::cout << "Couldn't load Image: " << fileloc << std::endl;
		}
	}
    // Because we have already copied image data into texture data  we can release memory used by image.
	ilDeleteImages(numTextures, imageIds);

	// Cleanup
	delete [] imageIds;
	imageIds = NULL;

	return 1;
}
