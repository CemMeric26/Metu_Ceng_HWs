import java.util.ArrayList;

public class PlaylistNodePrimaryIndex extends PlaylistNode {
	private ArrayList<Integer> audioIds;
	private ArrayList<PlaylistNode> children;
	
	public PlaylistNodePrimaryIndex(PlaylistNode parent) {
		super(parent);
		audioIds = new ArrayList<Integer>();
		children = new ArrayList<PlaylistNode>();
		this.type = PlaylistNodeType.Internal;
	}
	
	public PlaylistNodePrimaryIndex(PlaylistNode parent, ArrayList<Integer> audioIds, ArrayList<PlaylistNode> children) {
		super(parent);
		this.audioIds = audioIds;
		this.children = children;
		this.type = PlaylistNodeType.Internal;
	}
	
	// GUI Methods - Do not modify
	public ArrayList<PlaylistNode> getAllChildren()
	{
		return this.children;
	}
	
	public PlaylistNode getChildrenAt(Integer index) {return this.children.get(index); }
	
	public Integer audioIdCount()
	{
		return this.audioIds.size();
	}
	public Integer audioIdAtIndex(Integer index) {
		if(index >= this.audioIdCount() || index < 0) {
			return -1;
		}
		else {
			return this.audioIds.get(index);
		}
	}
	
	// Extra functions if needed
	//returns all audioIds
	public ArrayList<Integer> getAllaudioIds()
	{
		return this.audioIds;
	}
	//add audioId key to do ArrayList audioIds
	public void addAudioId(Integer index, Integer audioId)
	{
		audioIds.add(index,audioId);
	}
	// this will add audioId key to the ArrayList
	public void addAudioId(Integer audioId)
	{
		audioIds.add(audioId);
	}
	// this will add a child to the given Index in the arraylist of playlist node
	public void addChild(Integer index, PlaylistNode child)
	{
		children.add(index,child);
	}
	// this will add a child to the arraylist of playlist node
	public void addChild(PlaylistNode child)
	{
		children.add(child);
	}
	// this will set the audio ıd in the given index
	public void setAudioId(Integer index, Integer audioId)
	{
		audioIds.set(index,audioId);
	}
	// this will set the playlistnode child in the given index
	public void setChild(Integer index, PlaylistNode child)
	{
		children.set(index,child);
	}


}