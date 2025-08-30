import java.util.*;

class MeetingRoom{
    int id;
    int capacity;
    Calendar cal;
}

class MeetingRoomManager{
    List<MeetingRoom> meetRooms = new ArrayList<>(10);
}

class Calendar{
    int start;
    int end;
}

class User{
    int id;
    String name;
    String email;
}

class MeetingScheduler{
    MeetingRoom Scheduler(int people, int start, int end)
    {
        for(MeetingRoom mr : meetRooms)
        {
            if(mr.capacity>people && end<mr.cal.start) return mr;
        }
    }

}

public class Main {
    public static void main(String[] args) {
        MeetingScheduler ms = new MeetingScheduler();
        MeetingRoom availableRoom = ms.Scheduler(11,9,12);
        System.out.println("First available room "+availableRoom);
    }
}