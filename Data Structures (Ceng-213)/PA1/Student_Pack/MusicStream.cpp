#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    /* TODO */
    
    this->profiles.insertAtTheEnd(Profile(email,username,plan));
    
    
    
}

void MusicStream::deleteProfile(const std::string &email) {
    
    
    /* TODO */
    Node<Profile> *p;
    int i,j;
    p=profiles.getFirstNode();
    for(i=0;i<profiles.getSize();i++)
    {
        if((p->data).getEmail()==email)
        {
            break;
        }
        else
        {
            p=p->next;
        }

    }
    Node<Profile*> *px,*tp;
    px = ((p->data).getFollowers()).getFirstNode();
    tp=px;
    for(j=0;j<((p->data).getFollowers()).getSize();j++)
    {
        (px->data)->unfollowProfile(&(p->data));
        tp=tp->next;px=tp;
               
    }
    
    Node<Profile*> *py,*tm;
    py= ((p->data).getFollowings()).getFirstNode();
    tm=py;
    for(j=0;j<((p->data).getFollowings()).getSize();j++)
    {
        (p->data).unfollowProfile(py->data);
        tm=tm->next;py=tm;
        
    }
    
    
    LinkedList<Playlist> *play;
    play= &((p->data).getPlaylists());
    
    play->removeAllNodes();
    
    /*Node<Playlist> *ps; Node<Playlist> *tmp;
    ps=(p->data).getPlaylists().getFirstNode();
    
     tmp=ps;
    for(i=0;i<(p->data).getPlaylists().getSize();i++)
    {
        tmp=tmp->next;
        (p->data).deletePlaylist((ps->data).getPlaylistId()); 
        ps=tmp;std::cout<<"Hata burada mı";
        
    }
    delete tmp;delete ps;tmp=NULL;ps=NULL;*/
    

   
    this->profiles.removeNode(p);
}

void MusicStream::addArtist(const std::string &artistName) {
    /* TODO */
    this->artists.insertAtTheEnd(Artist(artistName));
    
    
    
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    /* TODO */
    int i;
    
    this->albums.insertAtTheEnd(Album(albumName));
    
    Node<Album> *a;

    a=albums.getFirstNode();
    for(i=0;i<albums.getSize();i++)
    {
        if((a->data).getName()==albumName)
        {
           break;
        }
        a=a->next;
    }
    Node<Artist> *as;
    as=artists.getFirstNode();
    for(i=0;i<artists.getSize();i++)
    {
        if((as->data).getArtistId()==artistId)
        {
           ( as->data).addAlbum(&(a->data));break;
        }
        as=as->next;
    }
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    /* TODO */
    this->songs.insertAtTheEnd(Song(songName,songDuration));
    
    int i;
    Node <Song> *s;
    s=songs.getFirstNode();
    for(i=0;i<songs.getSize();i++)
    {
        if((s->data).getName()==songName)
        {
            break;
        }
        s=s->next;
    }
    
    Node<Album> *a;a=albums.getFirstNode();
    for(i=0;i<albums.getSize();i++)
    {
        if((a->data).getAlbumId()==albumId)
        {
            (a->data).addSong(&(s->data));break;
            
        }
        a=a->next;
    }
 
    
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) 
{
    /* TODO */
    Node<Profile> *p1,*p2;
    int i;
    p1=profiles.getFirstNode();
    p2=profiles.getFirstNode();
    for(i=0;i<profiles.getSize();i++)
    {
        if((p1->data).getEmail()==email1)
        {
            break;
        }
        else
        {
            p1=p1->next;
        }
        
    }
    for(i=0;i<profiles.getSize();i++)
    {
        if((p2->data).getEmail()==email2)
        {
            break;
        }
        else
        {
            p2=p2->next;
        }
        
    }
    
    (p1->data).followProfile(&(p2->data));
    (p2->data).getFollowers().insertAtTheEnd(&(p1->data));
    
    
    
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) 
{
    /* TODO */
    Node<Profile> *p1,*p2;
    int i;
    p1=profiles.getFirstNode();p2=profiles.getFirstNode();
    for(i=0;i<profiles.getSize();i++)
    {
        if((p1->data).getEmail()==email1)
        {
            break;
        }
        else
        {
            p1=p1->next;
        }
        
    }
    for(i=0;i<profiles.getSize();i++)
    {
        if((p2->data).getEmail()==email2)
        {
            break;
        }
        else
        {
            p2=p2->next;
        }
        
    }
    
    (p1->data).unfollowProfile(&(p2->data));
    (p2->data).getFollowers().removeNode(&(p1->data));
    
    
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) 
{
    
    Node<Profile> *p1;
    int i;
    p1=profiles.getFirstNode();
    
    for(i=0;i<profiles.getSize();i++)
    {
        if((p1->data).getEmail()==email)
        {
            break;
        }
        p1=p1->next;
        
    }
    (p1->data).createPlaylist(playlistName);
    

}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) 
{
    
    
    Node<Profile> *p1;
    int i;
    p1=profiles.getFirstNode();
    for(i=0;i<profiles.getSize();i++)
    {
        if((p1->data).getEmail()==email)
        {
            break;
        }
        p1=p1->next;
        
    }
    (p1->data).deletePlaylist(playlistId);
    
    
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) 
{
    /* TODO */
    Node<Profile> *p1;
    Node<Song> *s;
    int i;
    
    p1=profiles.getFirstNode();
    for(i=0;i<profiles.getSize();i++)
    {
        if((p1->data).getEmail()==email)
        {
            break;
        }
        p1=p1->next;
        
    }
    
   
    
    s=songs.getFirstNode();
    
    for(i=0;i<songs.getSize();i++)
    {
        if((s->data).getSongId()==songId)
        {
            break;
        }
        s=s->next;
        
    }
    
    
    (p1->data).addSongToPlaylist(&(s->data),playlistId);
    
    
 
  
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) 
{
    /* TODO */
    Node<Profile> *p1;
    Node<Song> *s;
    int i;
    
    p1=profiles.getFirstNode();
    for(i=0;i<profiles.getSize();i++)
    {
        if((p1->data).getEmail()==email)
        {
            break;
        }
        p1=p1->next;
        
    }
    
   
    
    s=songs.getFirstNode();
    
    for(i=0;i<songs.getSize();i++)
    {
        if((s->data).getSongId()==songId)
        {
            break;
        }
        s=s->next;
        
    }
    
    
    (p1->data).deleteSongFromPlaylist(&(s->data),playlistId);

}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) 
{
    /* TODO */
    
    LinkedList<Song *> s; Node<Song*> *sg;
    Node<Profile> *p1;
    int i;
    p1=profiles.getFirstNode();
    
    for(i=0;i<profiles.getSize();i++)
    {
        if((p1->data).getEmail()==email)
        {
            break;
        }
        p1=p1->next;
        
    }
    
    sg=playlist->getSongs().getFirstNode();
    for(i=0;i<playlist->getSongs().getSize();i++)
    {
        
        s.insertAtTheEnd(sg->data);sg=sg->next;
    }
    
    
    if((p1->data).getPlan()==premium)
    {
        return s;
    }
    
    else
    {
        s.insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG),2);
    }
    

   return s;
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) 
{
    /* TODO */
    Playlist *ps;
    Node<Profile> *pr;
    pr=profiles.getFirstNode();
    int i;
    
    for(i=0;i<profiles.getSize();i++)
    {
        if((pr->data).getEmail()==email)
        {
            break;
        }
        pr=pr->next;
    
    }
    ps = (pr->data).getPlaylist(playlistId);
    
    
    
    return ps;
    

    
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) 
{
    /* TODO */
    /*AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA*/
    LinkedList<Playlist *> pla;
    Node<Profile> *pr;
    pr=profiles.getFirstNode();
    int i;
    
    for(i=0;i<profiles.getSize();i++)
    {
        if((pr->data).getEmail()==email)
        {
            break;
        }
        pr=pr->next;
    
    }
    pla=(pr->data).getSharedPlaylists();
    
    
    return pla;
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) 
{
    /* TODO */
    Node<Profile> *pr; Playlist *ps;
    pr=profiles.getFirstNode();
    int i;
    
    for(i=0;i<profiles.getSize();i++)
    {
        if((pr->data).getEmail()==email)
        {
            break;
        }
        pr=pr->next;
    
    }
    
    ps=(pr->data).getPlaylist(playlistId);
    ps->shuffle(seed);
    
    
    
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) 
{
    /* TODO */
    
    Node<Profile> *pr; Playlist *ps;
    pr=profiles.getFirstNode();
    int i;
    
    for(i=0;i<profiles.getSize();i++)
    {
        if((pr->data).getEmail()==email)
        {
            break;
        }
        pr=pr->next;
    
    }
    
    ps=(pr->data).getPlaylist(playlistId);
    ps->setShared(true);
    
    
    
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) 
{
    /* TODO */
    Node<Profile> *pr; Playlist *ps;
    pr=profiles.getFirstNode();
    int i;
    
    for(i=0;i<profiles.getSize();i++)
    {
        if((pr->data).getEmail()==email)
        {
            break;
        }
        pr=pr->next;
    
    }
    
    ps=(pr->data).getPlaylist(playlistId);
    ps->setShared(false);
}

void MusicStream::subscribePremium(const std::string &email) 
{
    /* TODO */
    Node<Profile> *pr; 
    pr=profiles.getFirstNode();
    int i;
    
    for(i=0;i<profiles.getSize();i++)
    {
        if((pr->data).getEmail()==email)
        {
            break;
        }
        pr=pr->next;
    
    }
    
    (pr->data).setPlan(premium);
    
}

void MusicStream::unsubscribePremium(const std::string &email) 
{
    /* TODO */
    Node<Profile> *pr;
    pr=profiles.getFirstNode();
    int i;
    
    for(i=0;i<profiles.getSize();i++)
    {
        if((pr->data).getEmail()==email)
        {
            break;
        }
        pr=pr->next;
    
    }
    
    (pr->data).setPlan(free_of_charge);
    
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
