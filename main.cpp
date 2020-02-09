#include <experimental\filesystem>
#include <iostream>

// handles culling of a given directory
void iterate_path( const std::experimental::filesystem::v1::path& path, bool recursively, const std::experimental::filesystem::v1::path& parent = {} )
{
	const auto remove = []( const std::experimental::filesystem::v1::path& f )
	{
		std::cout << "   >removed " << f.relative_path( ) << std::endl;
		std::experimental::filesystem::remove( f );		
	};

	for ( auto& file : std::experimental::filesystem::directory_iterator( path ) )
	{
		if ( !std::experimental::filesystem::is_directory( file ) )
			continue;

		if ( std::experimental::filesystem::is_empty( file ) )		
			remove( file );

		// directory isn't empty & has children directories, iterate them
		else if ( recursively )
			iterate_path( file, recursively, file );
	}

	// if we deleted all the children directories and in turn made the parent empty, delete it too
	if ( parent != std::experimental::filesystem::v1::path( ) && std::experimental::filesystem::is_empty( parent ) )	
		remove( parent );	
}

int main( )
{
	std::cout << "$> input directory" << std::endl;

	std::experimental::filesystem::path directory;
	while ( !std::cin.fail( ) && directory == std::experimental::filesystem::path( ) )
		std::cin >> directory;

	std::cout << "$> iterate each child directory? (y/n)" << std::endl;

	char response = 0;
	while ( !std::cin.fail( ) && response != 'y' && response != 'n' )
		std::cin >> response;

	std::cout << "$> searching " << directory << "..." << std::endl;
	iterate_path( directory, response == 'y' );
	std::cout << "$> finished." << std::endl;

	std::cin.clear( );
	std::cin.get( );
}