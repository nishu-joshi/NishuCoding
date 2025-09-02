import java.util.*;

//from here notitication banane ka process start

interface INotification{
    String getContent();
}

class SimpleNotification implements INotification{
    String text;
    SimpleNotification(String text){
        this.text=text;
    }

    @Override
    public String getContent(){
        return this.text;
    }
}

// interface INotificationDecorator{
//     INotification notification; //maybe static
// }

// class timeStampDecorator implements INotificationDecorator{
//     INotification notification; //maybe static
    
//     @Override
//     public String getContent(){
//         return INotification.getContent();
//     }
// }



//<singleton>> class
class NotificationService{
    List<INotification>notifications = new ArrayList<>();

    void sendNotifications(){

    }
}







//FROM here notification send krne ka process starts

interface IObservable{
    void add(IObserver obs);
    void remove(IObserver obs);
    void notifyObservers();
    void setNotification(INotification notification);
    INotification getNotification();
}


class NotificationObservable{
    List<IObserver>observers = new ArrayList<>();
    INotification currentNotification = null;
    
    public void add(IObserver obs){
        observers.add(obs);
    }

    public void remove(IObserver obs){
        observers.remove(obs);
    }

    public void notifyObservers(){
        for (IObserver iObserver : observers) {
            iObserver.Update();   
        }
    }


    public void setNotification(INotification notification){
        this.currentNotification = notification;
    }

    public INotification getNotification(){
        return this.currentNotification;
    }


    public String getNotificationContent(){
        return this.currentNotification.getContent();
    }
}


interface IObserver{
    void Update();
}

class NotificationEngine implements IObserver{
    NotificationObservable notification;
    
    @Override
    void Update(){

    }
}

interface NotificationStrategy{
    String content;
    void sendNotification();
}

class EmailStrategy implements NotificationStrategy{
    String content;
    void sendNotification(){


    }
}

class SMS implements NotificationStrategy{
    String content;
    void sendNotification(){

    }
}






public class NotificationSystem {
    public static void main(String[] args) {
        NotificationService ns = new NotificationService();

        SimpleNotification snotification = new SimpleNotification("Your order has been shipped");
    }
    
}
