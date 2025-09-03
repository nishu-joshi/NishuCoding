import java.util.*;

// Observer interface
interface IUser {
    void update(String channelName, String newVideo);
}

// Subject interface
interface IChannel {
    void subscribe(IUser user);

    void unsubscribe(IUser user);

    void notifyObservers(String newVideo);

    void uploadVideo(String title);
}

// Concrete Subject
class Channel implements IChannel {
    private String name;
    private List<IUser> subscribers = new ArrayList<>();

    Channel(String name) {
        this.name = name;
        System.out.println("New channel created: " + name);
    }

    @Override
    public void subscribe(IUser user) {
        subscribers.add(user);
        System.out.println(user + " subscribed to " + name);
    }

    @Override
    public void unsubscribe(IUser user) {
        subscribers.remove(user);
        System.out.println(user + " unsubscribed from " + name);
    }

    @Override
    public void notifyObservers(String newVideo) {
        for (IUser user : subscribers) {
            user.update(name, newVideo);
        }
    }

    @Override
    public void uploadVideo(String title) {
        System.out.println(name + " uploaded new video: " + title);
        notifyObservers(title);
    }

    @Override
    public String toString() {
        return name;
    }
}

// Concrete Observer
class User implements IUser {
    private String username;

    User(String username) {
        this.username = username;
        System.out.println("New user created: " + username);
    }

    @Override
    public void update(String channelName, String newVideo) {
        System.out.println(username + " got notified: " + channelName + " uploaded " + newVideo);
    }

    @Override
    public String toString() {
        return username;
    }
}

// Driver class
public class ObserverDesign {
    public static void main(String[] args) {
        Channel channel = new Channel("CarryMinati");
        User user1 = new User("Nishant");
        User user2 = new User("Aditya");

        channel.subscribe(user1);
        channel.subscribe(user2);

        channel.uploadVideo("Mast Roast");
        channel.unsubscribe(user1);
        channel.uploadVideo("Another Video");
    }
}
