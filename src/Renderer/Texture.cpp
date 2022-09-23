#define FOURCC(x) ( (unsigned int) (((x[3])<<24) | ((x[2])<<16) | ((x[1])<<8) | (x[0])) )

#include "Texture.h"

#include <fstream>

Texture::Texture() : m_slot( 0 ), m_width( 0 ), m_height( 0 ) {}

Texture::~Texture()
{
	glDeleteTextures( 1, &m_ID );
}

Texture& Texture::Load( const std::string& path )
{
	{
		auto it = s_Collection.find( path );
		if ( it != s_Collection.end() )
			return *it->second;
	}

	std::ifstream file( path, std::ios::in );

	if ( !file.is_open() )
	{
		printf( "Couldn't open %s!", path.c_str() );
		return *( Texture* )nullptr;
	}

	unsigned int filecode;
	file.read( ( char* ) &filecode, 4 );

	if ( filecode != FOURCC( "DDS " ) )
	{
		file.close();
		return *( Texture* )nullptr;
	}

	auto header = std::array<unsigned int, 31>();
	file.read( ( char* ) header.data(), sizeof( header ) );

	auto height = header[2];
	auto width = header[3];
	auto linearSize = header[4];
	auto mipMapCount = header[6];
	auto fourCC = header[20];

	auto bufferSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	auto* buffer = ( char* ) alloca( bufferSize * sizeof( char ) );

	file.read( buffer, bufferSize );

	auto components = ( fourCC == FOURCC( "DXT1" ) ) ? 3U : 4U;
	unsigned int format;

	switch ( fourCC )
	{
		case FOURCC( "DXT1" ):
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC( "DXT3" ):
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC( "DXT5" ):
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			return *( Texture* )nullptr;
	}

	// Create one OpenGL texture
	auto* texture = new Texture();
	glGenTextures( 1, &texture->m_ID );
	glBindTexture( GL_TEXTURE_2D, texture->m_ID );
	texture->m_width = width;
	texture->m_height = height;

	auto blockSize = ( format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ) ? 8U : 16U;
	auto offset = 0U;

	for ( auto level = 0U; level < mipMapCount && ( width || height ); level++ )
	{
		auto size = ( ( width + 3U ) / 4U ) * ( ( height + 3U ) / 4U ) * blockSize;
		glCompressedTexImage2D( GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset );

		offset += size;
		width >>= 1;
		height >>= 1;
	}

	s_Collection.emplace( path, texture );

	return *texture;
}

void Texture::Bind( unsigned int slot )
{
	m_slot = slot;
	glActiveTexture( GL_TEXTURE0 + slot );
	glBindTexture( GL_TEXTURE_2D, m_ID );
}

void Texture::Unbind()
{
	glBindTexture( GL_TEXTURE_2D, 0 );
}


unsigned int Texture::Slot() const
{
	return m_slot;
}

unsigned int Texture::Width() const
{
	return m_width;
}

unsigned int Texture::Height() const
{
	return m_height;
}

// std::array<Texture, 32> Texture::s_Slots = {};

std::unordered_map<std::string, std::unique_ptr<Texture>> Texture::s_Collection = {};