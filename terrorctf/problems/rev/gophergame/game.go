package main; import ("fmt"; "math/rand"; "time"; "os"); func check(e error) {if e != nil {panic(e)}}; func scram(inp string) string {rand.Seed(time.Now().Unix()); in := inp; inRune := []rune(in); rand.Shuffle(len(inRune), func(i, j int) {inRune[i], inRune[j] = inRune[j], inRune[i]}); rand.Shuffle(len(inRune), func(i, j int) {inRune[i], inRune[j] = inRune[j], inRune[i]}); return(string(inRune))}; func play() {var dlc string; for 1==1 {fmt.Println("Enter code for game DLC: "); fmt.Scanf("%s", &dlc); if dlc == scram(dlc) && len(dlc) == 10 {dat, err := os.ReadFile("gameflag.txt"); check(err); fmt.Println(string(dat)); break} else {fmt.Println("Wrong"); break}}}; func main() {var menu string = `
   ______            __              ______                   
  / ____/___  ____  / /_  ___  _____/ ____/___ _____ ___  ___ 
 / / __/ __ \/ __ \/ __ \/ _ \/ ___/ / __/ __ '/ __ '__ \/ _ \
/ /_/ / /_/ / /_/ / / / /  __/ /  / /_/ / /_/ / / / / / /  __/
\____/\____/ .___/_/ /_/\___/_/   \____/\__,_/_/ /_/ /_/\___/ 
          /_/     
Play - [X]       Exit - [Y]
`;fmt.Println("===============================================================");fmt.Println(menu);fmt.Println("===============================================================");fmt.Println("Can you GOpher?");var str string;for 1 == 1 {fmt.Println(">>> "); fmt.Scanf("%s", &str);fmt.Println("<<<");if str == "x" {play();break} else if str == "y" {break} }}
