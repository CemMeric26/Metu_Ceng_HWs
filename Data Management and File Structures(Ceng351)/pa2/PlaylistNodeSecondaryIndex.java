import java.util.ArrayList;

public class PlaylistNodeSecondaryIndex extends PlaylistNode {
	private ArrayList<String> genres;
	private ArrayList<PlaylistNode> children;

	public PlaylistNodeSecondaryIndex(PlaylistNode parent) {
		super(parent);
		genres = new ArrayList<String>();
		children = new ArrayList<PlaylistNode>();
		this.type = PlaylistNodeType.Internal;
	}
	
	public PlaylistNodeSecondaryIndex(PlaylistNode parent, ArrayList<String> genres, ArrayList<PlaylistNode> children) {
		super(parent);
		this.genres = genres;
		this.children = children;
		this.type = PlaylistNodeType.Internal;
	}
	
	// GUI Methods - Do not modify
	public ArrayList<PlaylistNode> getAllChildren()
	{
		return this.children;
	}
	
	public PlaylistNode getChildrenAt(Integer index) {
		
		return this.children.get(index);
	}
	

	public Integer genreCount()
	{
		return this.genres.size();
	}
	
	public String genreAtIndex(Integer index) {
		if(index >= this.genreCount() || index < 0) {
			return "Not Valid Index!!!";
		}
		else {
			return this.genres.get(index);
		}
	}

	// Extra functions if needed
	//returns genres arraylist
	public ArrayList<String> getAllGenres()
	{
		return this.genres;
	}
	//adds a genre to arraylist to the given index
	public void addGenre(Integer index, String genre)
	{
		genres.add(index,genre);
	}
	//adds a genre to arrayList
	public void addGenre(String genre)
	{
		genres.add(genre);
	}
	//adds a child to playlistnode arraylist at given index
	public void addChild(Integer index, PlaylistNode child)
	{
		children.add(index,child);
	}
	//adds a child to playlistnode arraylist
	public void addChild(PlaylistNode child)
	{
		children.add(child);
	}
	// sets teh genre in the given index
	public void setGenre(Integer index, String genre)
	{
		genres.set(index,genre);
	}
	// sets the child
	public void setChild(Integer index, PlaylistNode child)
	{
		children.set(index,child);
	}



}