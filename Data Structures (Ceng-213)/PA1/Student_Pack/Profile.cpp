#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {
    return this->username;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) {
    /* TODO */
    this->following.insertAtTheEnd(profile);
}

void Profile::unfollowProfile(Profile *profile) {
    /* TODO */
    this->following.removeNode(profile);
}

void Profile::createPlaylist(const std::string &playlistName) {
    /* TODO */
    
    this->playlists.insertAtTheEnd(Playlist(playlistName));
}

void Profile::deletePlaylist(int playlistId) {
    /* TODO */
    
    int i;
    Node<Playlist> *ps;
    
    ps=playlists.getFirstNode();
    
    for(i=0;i<playlists.getSize();i++)
    {
        if((ps->data).getPlaylistId()==playlistId)
        {
            playlists.removeNode(ps);break;
        }
        else
        {
            ps=ps->next;
        }
    }
}

void Profile::addSongToPlaylist(Song *song, int playlistId) {
    /* TODO */
    int i;
    for(i=0;i<playlists.getSize();i++)
    {
        if((playlists.getNodeAtIndex(i)->data).getPlaylistId()==playlistId)
        {
            
           ( playlists.getNodeAtIndex(i)->data).addSong(song);break;
        }
    }
    
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) {
    /* TODO */
    
    int i;
    Node<Playlist> *ps;
    ps=playlists.getFirstNode();
    
    for(i=0;i<playlists.getSize();i++)
    {
        if((ps->data).getPlaylistId()==playlistId)
        {
            
            (ps->data).dropSong(song);break;
        }
        else
        {
            ps=ps->next;
        }
    }
    
}

Playlist *Profile::getPlaylist(int playlistId) {
    /* TODO */
    int i;
    Node<Playlist> *p;
    
    p=playlists.getFirstNode();
    
    for(i=0;i<playlists.getSize();i++)
    {
        if((p->data).getPlaylistId()==playlistId)
        {
           break;
        }
        p=p->next;
    }
    return &(p->data);
}

LinkedList<Playlist *> Profile::getSharedPlaylists() 
{
    /* TODO */
    
    /*AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA*/
    LinkedList<Playlist *> pla; 
    Node <Playlist> *p;
    Node<Profile*> *pr;
    int i,j;
    
    pr=following.getFirstNode();
    
    for(i=0;i<following.getSize();i++)
    {
        p = (pr->data)->getPlaylists().getFirstNode();
        for(j=0;j<(pr->data)->getPlaylists().getSize();j++)
        {
            pla.insertAtTheEnd(&(p->data));
            p=p->next;
        }
        pr=pr->next;
    }
    
    return pla;
}

void Profile::shufflePlaylist(int playlistId, int seed) {
    /* TODO */
    
    int i;
    for(i=0;i<playlists.getSize();i++)
    {
        if((playlists.getNodeAtIndex(i)->data).getPlaylistId()==playlistId)
        {
          (playlists.getNodeAtIndex(i)->data).shuffle(seed);break;
        }
    }
    
}

void Profile::sharePlaylist(int playlistId) {
    /* TODO */
    
    int i;
    for(i=0;i<playlists.getSize();i++)
    {
        if((playlists.getNodeAtIndex(i)->data).getPlaylistId()==playlistId)
        {
            (playlists.getNodeAtIndex(i)->data).setShared(true);break;
        }
    }
    
    
}

void Profile::unsharePlaylist(int playlistId) {
    /* TODO */
    
    
    int i;
    for(i=0;i<playlists.getSize();i++)
    {
        if((playlists.getNodeAtIndex(i)->data).getPlaylistId()==playlistId)
        {
            (playlists.getNodeAtIndex(i)->data).setShared(false);break;
        }
    }
    
}

bool Profile::operator==(const Profile &rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }                                                   
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
