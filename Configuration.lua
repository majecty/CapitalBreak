is_full_screen = false--true--true -- full screen

default_frame_rate =  45

default_rate = 0.6 -- 시작할 때의 이자.

rate_rate = 0.634 -- 이자가 오르는 속도

default_limit = 100000 --  시작할 때의 카드 한도

limit_rate = 100000 --  한도가 오르는 속도

start_grade = 9 -- 9 is B+

char_velocity = 5--15

shop_count_for_upgrade = 10 -- 신용등급이 오르기 위해서 몇번 물건을 사야 하는가.

function lua_event_handler(event_id)
    io.stderr:write("here is lua file \n")
    --print_message_1("hahahahaha", 3)
    --print_message_2("hahahahaha")
    if event_id == "Description" then
        print_message_1("Welcome to the Break Capitalism", 2000)
    end
end

function message_handler(message_id)

    --io.stderr:write("haha\n")

    --io.stderr:write("ERROR: Received message_id is " + message_id + "\n")
    --io.stderr:write("/haha\n")
    if message_id == "Description" then
        print_message_1( "Welcome to the Break Capitalism", 1000)
    elseif message_id == "NoCard" then
        print_message_1("Contract with card company first.", 1000)
    elseif message_id == "EnterShop" then
        print_message_1("SA: Can I Help You?", 2000)
        print_message_2("SpaceBar: Buying Luxury", 2000)
    elseif message_id == "Buy" then
        print_message_1("Just Sign It!",500);
    elseif message_id == "EndNoInterest" then
        print_message_2("Your happy time is ended.",2000)
    elseif message_id == "CardStop" then
        print_message_1("Check your credit limit!",2000)
    elseif message_id == "DownGrade" then
        print_message_1("Your credit rating is diabolical.",1000)
    elseif message_id == "Upgrade" then
        print_message_1("You're very reliable",1000)
    elseif message_id == "EnterCardShop" then
        print_message_1("Officer: Thank you for visiting us",1000)
    elseif message_id == "GameOver" then
        print_message_1("Game Over",1000)
    elseif message_id == "HappyEnd" then
        print_message_1("Catch me if you can!",3000)
    elseif message_id == "GangPlus" then
        print_message_1("RUN! RUN! RUN!", 1000)
    elseif message_id == "ReceiveCard" then
        print_message_1("The card is added in your wallet. Good Luck", 1000)
    else
        io.stderr:write("ERROR: Received message_id is " + message_id + "\n")
    end
        io.stderr:write("ERROR: Received message_id is " + message_id + "\n")
    

end
