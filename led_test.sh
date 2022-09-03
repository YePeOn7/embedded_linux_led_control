LED_PATH="/sys/class/leds"
RED_LED_PATH="$LED_PATH/led_r"
GREEN_LED_PATH="$LED_PATH/led_g"
BLUE_LED_PATH="$LED_PATH/led_b"

setTriggerRed() { echo $1 > "$RED_LED_PATH/trigger"; }
setTriggerGreen() { echo $1 > "$GREEN_LED_PATH/trigger"; }
setTriggerBlue() { echo $1 > "$BLUE_LED_PATH/trigger"; }
setTriggerAll()
{
    setTriggerRed $1
    setTriggerGreen $1
    setTriggerBlue $1
}

if [ $# -eq 0 ]; then
    echo "Wrong parameter!"
fi

case $1 in
    trigger)
        case $2 in
            r)
                echo "set trigger red --> $3"
                setTriggerRed $3
                echo 
                ;;
            g)
                echo "set trigger green --> $3"
                setTriggerGreen $3
                ;;
            b)
                echo "set trigger blue --> $3"
                setTriggerBlue $3
                ;;
            all)
                echo "set trigger all --> $3"
                setTriggerAll $3
                ;;
            *)
                echo "wrong command..."
                ;;
        esac
        ;;
    
    delay_on)
        echo "set delay on $2"
        ;;

    delay_off)
        echo "set delay off $2"
        ;;
esac

# setTriggerAll input
# setTriggerRed heartbeat
# setTriggerGreen heartbeat
# setTriggerBlue heartbeat