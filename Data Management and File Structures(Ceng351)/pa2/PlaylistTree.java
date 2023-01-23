import java.util.ArrayList;
import java.util.Stack;

public class PlaylistTree {
	
	public PlaylistNode primaryRoot;		//root of the primary B+ tree
	public PlaylistNode secondaryRoot;	//root of the secondary B+ tree
	public PlaylistTree(Integer order) {
		PlaylistNode.order = order;
		primaryRoot = new PlaylistNodePrimaryLeaf(null);
		primaryRoot.level = 0;
		secondaryRoot = new PlaylistNodeSecondaryLeaf(null);
		secondaryRoot.level = 0;
	}

	//secondary b+tree is empty
	public void addSong(CengSong song) {
		// TODO: Implement this method new leaf node to its Internal parent node
		// add methods to fill both primary and secondary tree

		//Primary B+ TREE
		// the leaf which will I put my song
		PlaylistNodePrimaryLeaf insertingLeaf = findPrimaryIndexLeaf(song.audioId());
		//the songs in the leaf
		ArrayList<CengSong> leafSongs = insertingLeaf.getSongs();
		//the index that I will insert new song
		Integer insertingIndex = -1;
		//song number in the leaf
		Integer songs_size = insertingLeaf.songCount();
		Integer order_max = (2*PlaylistNode.order)+1;	// >2d over the limit
		Integer order_p = PlaylistNode.order;			// ==d the order


		// the  index I will insert my song in the leaf
		for (int i = 0; i < songs_size ; i++)
		{
			if (leafSongs.get(i).audioId() > song.audioId())
			{
				insertingIndex = i;
				break;
			}
		}
		if (insertingIndex == -1)
		{
			insertingIndex = insertingLeaf.songCount();
		}

		// Insert song to the tree
		insertingLeaf.addSong(insertingIndex, song);

		// if our leaf is the root
		if(insertingLeaf.getParent() == null)
		{
			// if overflow happens in our root  order <=2n at max
			// its leaf and root at the same time
			if(insertingLeaf.songCount() == order_max )
			{
				//spliting operation of overflow nodes
				PlaylistNodePrimaryIndex newRoot = new PlaylistNodePrimaryIndex(null); //new root it is
				PlaylistNodePrimaryLeaf newNode = new PlaylistNodePrimaryLeaf(newRoot);  // right node it is

				for(int i = order_p,j=0;i<insertingLeaf.songCount();i++,j++)
				{
					//adding childs in last d keys of the leaf to the new right leaf
					newNode.addSong(j,insertingLeaf.songAtIndex(i));
				}
				//clearing right side of the leaf
				insertingLeaf.getSongs().subList(PlaylistNode.order,insertingLeaf.getSongs().size()).clear();
				insertingLeaf.setParent(newRoot);

				//second childs first audioId is added as key in the root
				newRoot.addAudioId(0,newNode.songAtIndex(0).audioId()); //right node's first key is copied to the root
				//inserting leaf has the first d keys childs
				newRoot.addChild(0,insertingLeaf);
				//new node has previous leafs last d keys childs
				newRoot.addChild(1,newNode);
				//updating the root
				primaryRoot = newRoot;

			}

		}

		// if our leaf is not the root
		else
		{
			//if overflow in the leaf node
			if(insertingLeaf.songCount() == order_max)
			{
				//dividing the node into two sides and filling them
				PlaylistNode parent_of_leaf = insertingLeaf.getParent();
				PlaylistNodePrimaryLeaf newNode = new PlaylistNodePrimaryLeaf(parent_of_leaf);
				for(int i=order_p,j=0;i<insertingLeaf.songCount();i++,j++)
				{
					//inserting songs in the last d keys
					newNode.addSong(j,insertingLeaf.songAtIndex(i));
				}
				//removing last d keys from previous node
				insertingLeaf.getSongs().subList(order_p,insertingLeaf.getSongs().size()).clear();
				//adding new leaf node to its parent node
				Integer putKey = newNode.audioIdAtIndex(0);
				boolean flag2 = false;
				Integer parent_key_count = ((PlaylistNodePrimaryIndex) parent_of_leaf).audioIdCount();

				for(int i=0;i<parent_key_count;i++)
				{
					if(((PlaylistNodePrimaryIndex)parent_of_leaf).audioIdAtIndex(i)>putKey)
					{
						//adding key value in the parent node in its position
						((PlaylistNodePrimaryIndex)parent_of_leaf).addAudioId(i,putKey);
						//adding newNode tot the child list of its parent
						((PlaylistNodePrimaryIndex)parent_of_leaf).addChild(i+1,newNode);
						flag2 = true;
						break;
					}
				}
				if(!flag2)
				{
					//add to the last position because index is bigger than all of em
					((PlaylistNodePrimaryIndex)parent_of_leaf).addAudioId(putKey);
					((PlaylistNodePrimaryIndex)parent_of_leaf).addChild(newNode);
				}

				//****ORDINARY OPERATION COMPLETED****

				//let's check if any overflow happened in parent
				PlaylistNode nextParent;
				while (((PlaylistNodePrimaryIndex)parent_of_leaf).audioIdCount() == order_max)
				{
					flag2 = false;
					nextParent =  parent_of_leaf.getParent();

					//if Internal parent node is root
					if(nextParent == null)
					{

						//new root created
						PlaylistNodePrimaryIndex newRoot = new PlaylistNodePrimaryIndex(null);
						//new internal node created
						PlaylistNodePrimaryIndex newInternalNode = new PlaylistNodePrimaryIndex(newRoot);

						//helper function for filling the internal node and removing the extra items from old internal node
						putKey = NodeOverFlowInsert((PlaylistNodePrimaryIndex) parent_of_leaf, newInternalNode );
						


						//putKey = ((PlaylistNodePrimaryIndex)parent_of_leaf).audioIdAtIndex(PlaylistNode.order);
						
						//newInternalNode to the newRoot
						newRoot.addAudioId(0,putKey);
						newRoot.addChild(0,parent_of_leaf);
						parent_of_leaf.setParent(newRoot);
						newRoot.addChild(1,newInternalNode);
						primaryRoot = newRoot;
						break;


					}
					//if parent node is ordinary node
					else
					{
						PlaylistNodePrimaryIndex newInternalNode = new PlaylistNodePrimaryIndex(nextParent);

						// helper func for fillling the newInternal Node and removing extra items fro old internal node
						putKey = NodeOverFlowInsert((PlaylistNodePrimaryIndex) parent_of_leaf, newInternalNode);
								

						//putKey = ((PlaylistNodePrimaryIndex)parent_of_leaf).audioIdAtIndex(PlaylistNode.order);

						//*****************
						for(int i = 0; i<((PlaylistNodePrimaryIndex)nextParent).audioIdCount(); i++ )
						{
							if(((PlaylistNodePrimaryIndex)nextParent).audioIdAtIndex(i)>putKey)
							{
								((PlaylistNodePrimaryIndex)nextParent).addAudioId(i,putKey);
								((PlaylistNodePrimaryIndex)nextParent).addChild(i,parent_of_leaf);
								//setting child in the specific index
								((PlaylistNodePrimaryIndex)nextParent).setChild(i+1,newInternalNode);
								flag2 = true;
								break;
							}
						}
						if(!flag2)
						{
							((PlaylistNodePrimaryIndex)nextParent).addAudioId(putKey);
							//adding the child at the end nothing to point for that child
							((PlaylistNodePrimaryIndex)nextParent).addChild(newInternalNode);
						}
						//****************************

						parent_of_leaf = nextParent;
					}
				}

			}
		}

		//******************************************************
		//-----SECONDARY B+TREE IMPLEMENTATION FOR ADDSONG------
		// the leaf which will I put my song
		PlaylistNodeSecondaryLeaf insertingSECLeaf = findSecondaryIndexLeaf(song.genre());
		
		//the songs in the leaf
		ArrayList<ArrayList<CengSong>> leafSongBucket = insertingSECLeaf.getSongBucket();
		
		//the index that I will insert new song
		Integer insertingSECIndex = -1;
		boolean added = false;
		//song number in the leaf
		Integer songBucket_size = insertingSECLeaf.genreCount();

		for(int i=0;i<songBucket_size;i++)
		{
			if((insertingSECLeaf.genreAtIndex(i)).compareTo(song.genre()) == 0 )
			{
				leafSongBucket.get(i).add(song);
				added = true;
				break;
			}
			else if((insertingSECLeaf.genreAtIndex(i)).compareTo(song.genre()) > 0 )
			{
				insertingSECIndex = i;
				break;

			}
		}
		if(insertingSECIndex == -1)
		{
			insertingSECIndex = insertingSECLeaf.genreCount();
		}
		//inserting the song in the songBUcket's arrayList
		if(!added)
		{

			//leafSongBucket.get(insertingSECIndex).add(song);
			insertingSECLeaf.addSong(insertingSECIndex,song);
		}

		// if our leaf is the root
		if(insertingSECLeaf.getParent() == null)
		{
			// if overflow happens in our root  order <=2n at max
			// its leaf and root at the same time
			if(insertingSECLeaf.genreCount() == order_max )
			{
				//spliting operation of overflow nodes
				PlaylistNodeSecondaryIndex newSECRoot = new PlaylistNodeSecondaryIndex(null); //new root it is
				PlaylistNodeSecondaryLeaf newSECNode = new PlaylistNodeSecondaryLeaf(newSECRoot);  // right node it is

				for(int i = order_p,j=0;i<insertingSECLeaf.genreCount();i++,j++)
				{
					//adding childs in last d keys of the leaf to the new right leaf
					newSECNode.getSongBucket().add(insertingSECLeaf.songsAtIndex(i));
				}

				//clearing right side of the leaf
				insertingSECLeaf.getSongBucket().subList(PlaylistNode.order,insertingSECLeaf.getSongBucket().size()).clear();
				insertingSECLeaf.setParent(newSECRoot);

				//second childs first audioId is added as key in the root
				newSECRoot.addGenre(0,newSECNode.genreAtIndex(0)); //right node's first key is copied to the root
				//inserting leaf has the first d keys childs
				newSECRoot.addChild(0,insertingSECLeaf);
				//new node has previous leafs last d keys childs
				newSECRoot.addChild(1,newSECNode);
				//updating the root
				secondaryRoot = newSECRoot;

			}

		}
		//if sec_leaf is not the root 
		else
		{
			//if overflow in the leaf node
			if(insertingSECLeaf.genreCount() == order_max )
			{
				//dividing the node into two sides and filling them
				PlaylistNode parent_SEC = insertingSECLeaf.getParent();
				PlaylistNodeSecondaryLeaf newSECNode = new PlaylistNodeSecondaryLeaf(parent_SEC);
				for(int i=order_p,j=0;i<insertingSECLeaf.genreCount();i++,j++)
				{
					//inserting songs in the last d keys
					newSECNode.getSongBucket().add(insertingSECLeaf.songsAtIndex(i));
				}

				//removing last d keys from previous node
				insertingSECLeaf.getSongBucket().subList(PlaylistNode.order,insertingSECLeaf.getSongBucket().size()).clear();

				//adding new leaf node to its parent node
				String putGenre = newSECNode.genreAtIndex(0);
				boolean flag2 = false;
				Integer parent_key_count = ((PlaylistNodeSecondaryIndex) parent_SEC).genreCount();

				for(int i=0;i<parent_key_count;i++)
				{
					if(((PlaylistNodeSecondaryIndex)parent_SEC).genreAtIndex(i).compareTo(putGenre) > 0)
					{
						//adding key value in the parent node in its position
						((PlaylistNodeSecondaryIndex)parent_SEC).addGenre(i,putGenre);
						//adding newSECNode tot the child list of its parent
						((PlaylistNodeSecondaryIndex)parent_SEC).addChild(i+1,newSECNode);
						flag2 = true;
						break;
					}
				}

				if(!flag2)
				{
					//add to the last position because index is bigger than all of em
					((PlaylistNodeSecondaryIndex)parent_SEC).addGenre(putGenre);
					((PlaylistNodeSecondaryIndex)parent_SEC).addChild(newSECNode);
				}

				//------------ORDINARY OPERATION COMPLETED--------------------------------
				//let's check if any overflow happened in parent
				PlaylistNode nextSECParent;
				while (((PlaylistNodeSecondaryIndex)parent_SEC).genreCount() == order_max)
				{
					flag2 = false;
					nextSECParent =  parent_SEC.getParent();

					//if Internal parent node is root
					if(nextSECParent == null)
					{

						//new root created
						PlaylistNodeSecondaryIndex newRootSEC = new PlaylistNodeSecondaryIndex(null);
						//new internal node created
						PlaylistNodeSecondaryIndex newInternalNodeSEC = new PlaylistNodeSecondaryIndex(newRootSEC);

						//helper function for filling the internal node and removing the extra items from old internal node
						putGenre = NodeOverFlowInsertForSEC((PlaylistNodeSecondaryIndex) parent_SEC, newInternalNodeSEC );
						
			
						//newInternalNode to the newRoot
						newRootSEC.addGenre(0,putGenre);
						newRootSEC.addChild(0,parent_SEC);
						parent_SEC.setParent(newRootSEC);
						newRootSEC.addChild(1,newInternalNodeSEC);
						secondaryRoot = newRootSEC;
						break;


					}

					//if parent node is ordinary node
					else
					{
						PlaylistNodeSecondaryIndex newInternalNodeSEC = new PlaylistNodeSecondaryIndex(nextSECParent);

						// helper func for fillling the newInternal Node and removing extra items fro old internal node
						putGenre = NodeOverFlowInsertForSEC((PlaylistNodeSecondaryIndex) parent_SEC, newInternalNodeSEC);
								
						//*****************
						for(int i = 0; i<((PlaylistNodeSecondaryIndex)nextSECParent).genreCount(); i++ )
						{
							if(((PlaylistNodeSecondaryIndex)nextSECParent).genreAtIndex(i).compareTo(putGenre) > 0)
							{
								((PlaylistNodeSecondaryIndex)nextSECParent).addGenre(i,putGenre);
								((PlaylistNodeSecondaryIndex)nextSECParent).addChild(i,parent_SEC);
								//setting child in the specific index
								((PlaylistNodeSecondaryIndex)nextSECParent).setChild(i+1,newInternalNodeSEC);
								flag2 = true;
								break;
							}
						}
						if(!flag2)
						{
							((PlaylistNodeSecondaryIndex)nextSECParent).addGenre(putGenre);
							//adding the child at the end nothing to point for that child
							((PlaylistNodeSecondaryIndex)nextSECParent).addChild(newInternalNodeSEC);
						}
						//****************************

						parent_SEC = nextSECParent;
					}
				}

			}
		}




		return;
	}

	//------------------overflow handling function for PRIMARY---------------------------
	public Integer NodeOverFlowInsert( PlaylistNodePrimaryIndex parent_of_leaf , PlaylistNodePrimaryIndex newNode )
	{
		//new internal node created
		Integer putKey;

		//Integer parent_count = (  parent_of_leaf ).audioIdCount();
		// putting keys and childs of new node
		for(int i = PlaylistNode.order + 1,j=0; i< (  parent_of_leaf ).audioIdCount();i++,j++)
		{
			newNode.addAudioId(j,(parent_of_leaf).audioIdAtIndex(i));
			newNode.addChild(j,(parent_of_leaf).getChildrenAt(i));
			(parent_of_leaf).getChildrenAt(i).setParent(newNode);

		}
		newNode.addChild(newNode.audioIdCount(),(parent_of_leaf).getChildrenAt((  parent_of_leaf ).audioIdCount()));
		(parent_of_leaf).getChildrenAt((  parent_of_leaf ).audioIdCount()).setParent(newNode);

		putKey = ((PlaylistNodePrimaryIndex)parent_of_leaf).audioIdAtIndex(PlaylistNode.order);

		//removing extra items from old node
		(parent_of_leaf).getAllaudioIds().subList(PlaylistNode.order,(parent_of_leaf).getAllaudioIds().size()).clear();
		(parent_of_leaf).getAllChildren().subList(PlaylistNode.order+1,(parent_of_leaf).getAllChildren().size()).clear();

		return putKey;
	}

	//------------------overflow handling function for SECONDARY---------------------------
	public String NodeOverFlowInsertForSEC( PlaylistNodeSecondaryIndex parent_SEC , PlaylistNodeSecondaryIndex newInternalNodeSEC )
	{
		//new internal node created
		String putGenre;

		// putting keys and childs of new node
		for(int i = PlaylistNode.order + 1,j=0; i< ( parent_SEC).genreCount();i++,j++)
		{
			newInternalNodeSEC.addGenre(j,(parent_SEC).genreAtIndex(i));
			newInternalNodeSEC.addChild(j,(parent_SEC).getChildrenAt(i));
			(parent_SEC).getChildrenAt(i).setParent(newInternalNodeSEC);

		}
		newInternalNodeSEC.addChild(newInternalNodeSEC.genreCount(),(parent_SEC).getChildrenAt((parent_SEC).genreCount()));
		(parent_SEC).getChildrenAt((parent_SEC).genreCount()).setParent(newInternalNodeSEC);

		putGenre = ((PlaylistNodeSecondaryIndex)parent_SEC).genreAtIndex(PlaylistNode.order);

		//removing extra items from old node
		(parent_SEC).getAllGenres().subList(PlaylistNode.order,(parent_SEC).getAllGenres().size()).clear();
		(parent_SEC).getAllChildren().subList(PlaylistNode.order+1,(parent_SEC).getAllChildren().size()).clear();

		return putGenre;
	}


	public PlaylistNodePrimaryLeaf findPrimaryIndexLeaf(Integer audioId)
	{
		PlaylistNode curr_node = primaryRoot;
		boolean flag;

		while(curr_node.getType() == PlaylistNodeType.Internal )
		{
			flag = false;
			Integer curr_node_size = ((PlaylistNodePrimaryIndex) curr_node).audioIdCount();

			for(int i=0; i < curr_node_size;i++ )
			{
				if(((PlaylistNodePrimaryIndex) curr_node).audioIdAtIndex(i) > audioId)
				{
					curr_node = ((PlaylistNodePrimaryIndex) curr_node).getChildrenAt(i);
					flag = true;
					break;
				}

			}
			if(!flag)
			{
				curr_node = ((PlaylistNodePrimaryIndex) curr_node).getChildrenAt( ((PlaylistNodePrimaryIndex) curr_node).audioIdCount());
			}
		}

		return ((PlaylistNodePrimaryLeaf) curr_node);
	}

	public PlaylistNodeSecondaryLeaf findSecondaryIndexLeaf(String genre)
	{
		PlaylistNode curr_node = secondaryRoot;
		boolean flag;

		while(curr_node.getType() == PlaylistNodeType.Internal)
		{
			flag = false;
			Integer curr_node_size = ((PlaylistNodeSecondaryIndex) curr_node).genreCount();

			for(int i=0;i<curr_node_size;i++)
			{
				// if the ith key is greater than our key, then i should be the next chilld's index
				if( (((PlaylistNodeSecondaryIndex) curr_node).genreAtIndex(i)).compareTo(genre) > 0 )
				{
					curr_node = ((PlaylistNodeSecondaryIndex) curr_node).getChildrenAt(i);
					flag=true;
					break;
				}


			}

			if(!flag)
			{
				curr_node = ((PlaylistNodeSecondaryIndex) curr_node).getChildrenAt(((PlaylistNodeSecondaryIndex) curr_node).genreCount());
			}
		}

		return ((PlaylistNodeSecondaryLeaf) curr_node);
	}


	public CengSong searchSong(Integer audioId) {
		// TODO: Implement this method
		// find the song with the searched audioId in primary B+ tree
		// return value will not be tested, just print according to the specifications

		PlaylistNode p_node = primaryRoot ;
		boolean flag;
		Integer tab_size=0;
		while(p_node.getType() == PlaylistNodeType.Internal)
		{

			for(int j=0;j<tab_size;j++)
				System.out.print("\t");

			System.out.print("<index>\n");
			Integer audioIdCount = ((PlaylistNodePrimaryIndex) p_node).audioIdCount();
			for(int i=0;i<audioIdCount;i++)
			{
				for(int j=0;j<tab_size;j++)
					System.out.print("\t");
				
				System.out.print(((PlaylistNodePrimaryIndex) p_node).audioIdAtIndex(i));
				System.out.print("\n");
			}
			for(int j=0;j<tab_size;j++)
				System.out.print("\t");
			System.out.print("</index>\n");
		
			flag=false;
			for(int i = 0; i<audioIdCount;i++)
			{
				if(((PlaylistNodePrimaryIndex) p_node).audioIdAtIndex(i)>audioId)
				{
					p_node = ((PlaylistNodePrimaryIndex) p_node).getChildrenAt(i);
					flag = true;
					break;
				}
			}
			if(!flag)
			{
				p_node = ((PlaylistNodePrimaryIndex) p_node).getChildrenAt(((PlaylistNodePrimaryIndex) p_node).audioIdCount());
			}
			tab_size++;
		}
		Integer song_count = ((PlaylistNodePrimaryLeaf) p_node).songCount();
		for(int i = 0;i<song_count;i++)
		{
			if(((PlaylistNodePrimaryLeaf) p_node).audioIdAtIndex(i) == audioId)
			{
				for(int j=0;j<tab_size;j++)
					System.out.print("\t");
				System.out.print("<data>\n");
				for(int j=0;j<tab_size;j++)
					System.out.print("\t");
				System.out.print("<record>");
				System.out.print(((PlaylistNodePrimaryLeaf) p_node).songAtIndex(i).audioId());
				System.out.print("|");
				System.out.print(((PlaylistNodePrimaryLeaf) p_node).songAtIndex(i).genre());
				System.out.print("|");
				System.out.print(((PlaylistNodePrimaryLeaf) p_node).songAtIndex(i).songName());
				System.out.print("|");
				System.out.print(((PlaylistNodePrimaryLeaf) p_node).songAtIndex(i).artist());
				System.out.print("</record>\n");
				for(int j=0;j<tab_size;j++)
					System.out.print("\t");
				System.out.print("</data>\n");
				return (((PlaylistNodePrimaryLeaf) p_node).songAtIndex(i));
			}
		}
		System.out.print("Could not find ");
		System.out.print(audioId);
		return null;
	}
	
	
	public void printPrimaryPlaylist() 
	{
		// TODO: Implement this method
		// print the primary B+ tree in Depth-first order
		Stack<PlaylistNode> nodeStack = new Stack<PlaylistNode>();
		Stack<Integer> tabStack = new Stack<Integer>();
		PlaylistNode root = primaryRoot;
		boolean leaf_alert = false;
		Integer tab_size=0,tab_internal=0,tab_leaf=0;
		nodeStack.add(root);
		tabStack.add(0);

		while(!nodeStack.isEmpty())
		{
			PlaylistNode primaryNode = nodeStack.pop();
			tab_size = tabStack.pop();
			//if primary node is internal node
		

			if(primaryNode.getType() == PlaylistNodeType.Internal)
			{
				leaf_alert = false;
				//pushing all childs to the stack by order of them
				ArrayList<PlaylistNode> primaryChildren = ((PlaylistNodePrimaryIndex)primaryNode).getAllChildren();
				Integer primaryChildrenSize = primaryChildren.size()-1;
				
				for (int i=primaryChildrenSize;i>=0;i-- )
				{
					nodeStack.add(primaryChildren.get(i));
					tabStack.add(tab_size+1);
				}

				
				// print keys all audioIDS on this internal node

				for(int j=0;j<tab_size;j++)
					System.out.print("\t");

				System.out.print("<index>\n");
				Integer pnode_IDsize = ((PlaylistNodePrimaryIndex) primaryNode).audioIdCount();
				for (int i = 0; i < pnode_IDsize ; i++)
				{
					for(int j=0;j<tab_size;j++)
						System.out.print("\t");

					System.out.print(((PlaylistNodePrimaryIndex) primaryNode).audioIdAtIndex(i));
					System.out.print("\n");	
				}
				for(int j=0;j<tab_size;j++)
					System.out.print("\t");
					
				System.out.print("</index>\n");

			}


			if (primaryNode.getType() == PlaylistNodeType.Leaf)
			{
				
				// print all songs in order
				for(int j=0;j<tab_size;j++)
						System.out.print("\t");

				System.out.print("<data>\n");
				Integer song_count = ((PlaylistNodePrimaryLeaf) primaryNode).songCount();
				for (int i = 0; i < song_count; i++)
				{
					for(int j=0;j<tab_size;j++)
						System.out.print("\t");

					System.out.print("<record>");					
					System.out.print(((PlaylistNodePrimaryLeaf) primaryNode).songAtIndex(i).fullName());
					System.out.print("</record>\n");
				}
				for(int j=0;j<tab_size;j++)
						System.out.print("\t");
				System.out.print("</data>\n");

				
				
			}
			

		}

	}

	//this is a
	public void printSecondaryPlaylist() {
		// TODO: Implement this method
		// print the secondary B+ tree in Depth-first order
		Stack<PlaylistNode> nodeStack = new Stack<PlaylistNode>();
		Stack<Integer> tabStack = new Stack<Integer>();
		PlaylistNode root = secondaryRoot;
		boolean leaf_alert = false;
		Integer tab_size=0,tab_internal=0,tab_leaf=0;
		nodeStack.add(root);
		tabStack.add(0);

		while(!nodeStack.isEmpty())
		{
			PlaylistNode secondaryNode = nodeStack.pop();
			tab_size = tabStack.pop();
			//if primary node is internal node
		

			if(secondaryNode.getType() == PlaylistNodeType.Internal)
			{
				leaf_alert = false;
				//pushing all childs to the stack by order of them
				ArrayList<PlaylistNode> secondaryChildren = ((PlaylistNodeSecondaryIndex)secondaryNode).getAllChildren();
				Integer secondaryChildrenSize = secondaryChildren.size()-1;
				
				for (int i=secondaryChildrenSize;i>=0;i-- )
				{
					nodeStack.add(secondaryChildren.get(i));
					tabStack.add(tab_size+1);
				}

				// print keys all genres on this internal node

				for(int j=0;j<tab_size;j++)
					System.out.print("\t");

				System.out.print("<index>\n");
				Integer pnode_IDsize = ((PlaylistNodeSecondaryIndex) secondaryNode).genreCount();
				for (int i = 0; i < pnode_IDsize ; i++)
				{
					for(int j=0;j<tab_size;j++)
						System.out.print("\t");

					System.out.print(((PlaylistNodeSecondaryIndex) secondaryNode).genreAtIndex(i));
					System.out.print("\n");	
				}
				for(int j=0;j<tab_size;j++)
					System.out.print("\t");
					
				System.out.print("</index>\n");

			}


			if (secondaryNode.getType() == PlaylistNodeType.Leaf)
			{
				
				// print all songs in order
				for(int j=0;j<tab_size;j++)
						System.out.print("\t");

				System.out.print("<data>\n");
				
				Integer song_count = ((PlaylistNodeSecondaryLeaf) secondaryNode).genreCount();
				for (int i = 0; i < song_count; i++)
				{
										
					//System.out.print(((PlaylistNodeSecondaryLeaf) secondaryNode).songAtIndex(i).fullName());
					for(int j=0;j<tab_size;j++)
						System.out.print("\t");

					System.out.print(((PlaylistNodeSecondaryLeaf) secondaryNode).genreAtIndex(i));
					System.out.print("\n");
					ArrayList<CengSong> inside_songs = ((PlaylistNodeSecondaryLeaf) secondaryNode).songsAtIndex(i);
					for(int k=0;k<inside_songs.size();k++)
					{
						for(int j=0;j<tab_size+1;j++)
							System.out.print("\t");
						
						System.out.print("<record>");
						System.out.print(inside_songs.get(k).fullName());
						System.out.print("</record>\n");
						

					}
					
				}
				for(int j=0;j<tab_size;j++)
					System.out.print("\t");
				
				System.out.print("</data>\n");

				
				
			}
			

		}

		return;
	}
	
	// Extra functions if needed

}

