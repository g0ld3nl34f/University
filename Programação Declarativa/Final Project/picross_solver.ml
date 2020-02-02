let rec length = function 
	|[] -> 0
	| _::x -> 1 + length x;;

let rec append l1 l2 =
	match l1 with
	|[] -> l2
	|h::s -> h::(append s l2);;

let rec remove_tail = function
	|[] -> []
	|h::[] -> []
	|h::t -> h::(remove_tail t);;

let rec to_fill l =
	match l with
	|[] -> 0
	|[e] -> e
	|h::t -> (to_fill t) + h + 1;;

let rec fill_this_much l x = x - to_fill l;;

let rec fill_clue c f = if c>0 && f=0 then 1::(fill_clue (c-1) f) else 
	if c-f>0 && f>0 then 0::(fill_clue (c-1) (f-1)) else [0];;

let rec no_clue c = if c>0 then 0::(no_clue (c-1)) else [0];;

let rec complete x = if x > 0 then 0::(complete (x-1)) else [];;

let rec simple_box l x =
	match l with
	|[] -> [] 
	|h::t -> if h-x > 0 then append (fill_clue h x) (simple_box t x) else append (no_clue h) (simple_box t x);;

let line_solver l x =
	if (length (simple_box l (fill_this_much l x))) < x then append (simple_box l (fill_this_much l x)) (complete (x-(length (simple_box l (fill_this_much l x))))) else 
		simple_box l (fill_this_much l x);;

let line_solver_checker l x = if length(line_solver l x) > x then remove_tail (line_solver l x) else line_solver l x;;

let rec print_list = function
	|[] -> ()
	|h::t -> if h = 1 then print_string "x" else print_string "."; 
		print_string " "; print_list t;;

let rec print_grid = function
	|[] -> ()
	|h::t -> print_list h; print_string "\n"; print_grid t;;

let rec count l =
	match l with
	|[] -> 0
	|h::t -> 1 + (count t);;

let rec solve_lines l s =
	match l with
	|[] -> []
	|h::t -> line_solver_checker h s::(solve_lines t s);;

let get_head  = function h::t -> h;;

let rec get_heads = function
	|[] -> []
	|(h::r)::t -> h::(get_heads t);;

let rec remove_head = function
	|[] -> []
	|h::t -> t;;

let rec remove_heads = function
	|[] -> []
	|h::t -> (remove_head h)::(remove_heads t);;

let compare = function x -> function y -> if x = 1 || y = 1 then 1 else 0;;

let rec compare_list l1 l2 =
	match l1 with 
	|[] -> []
	|h::t -> if (length l2) > 0 then compare h (get_head l2) :: compare_list t (remove_head l2) else [];;

let rec merge l1 l2 =
	match l1 with
	|[] -> []
	|h::t -> (compare_list h (get_heads l2))::(merge t (remove_heads l2));;

let solve_simple_box h t = merge (solve_lines h (count t)) (solve_lines t (count h));;

let rec count_list = function
	|[] -> 0
	|h::t -> h + (count_list t);;

let rec check_if_clue_found possible x =
	match possible with
	|[] -> true
	|h::t -> if x > 0 then if h = 0 then false else (check_if_clue_found t (x-1)) else true;;

let rec remove_checked x = function 
	|[] -> []
	|h::t -> if x > 0 then remove_checked (x - 1) t else h::t;;

let rec check_if_line_solved clues possible =
	match (clues, possible) with
	|[], [] -> true
	|[0], [] -> true
	|(h::t), [] -> false
	|[], (hp::tp) -> if hp = 1 then false else check_if_line_solved [] tp
	|(h::t), (hp::tp) -> if h > 0 then if hp = 0 then check_if_line_solved (h::t) tp else 
							if (check_if_clue_found (hp::tp) h) then check_if_line_solved t (remove_checked (h-1) tp) else false
								else if hp = 1 then false else check_if_line_solved t tp;;

let rec check_lines_solved lines_clues possible_answer =
	match (lines_clues, possible_answer) with
	|[], [] -> true
	|(h::t), (hp::tp) -> if (check_if_line_solved h hp) then check_lines_solved t tp else false;;

let rec set_spaces = function 
	|[] -> []
	|h::t -> 1 :: set_spaces t;;

let rec set_min = function h::t ->  0 :: set_spaces t;;

let rec set_max_rest x = function
	|[] -> []
	|h::t -> x :: set_max_rest x t;;

let rec set_max x = function h::t -> (x - 1) :: (set_max_rest x t);;

let rec get_max_spaces = function
	|[] -> 0
	|h::t -> if h = 0 then (1 + (get_max_spaces t)) else get_max_spaces t;;

let get_max_space_size x l = x - ((count_list l) + ((length l)-1));; 

let rec check_possible curr max =
	match (curr, max) with
	|[], [] -> true
	|(h::t), (hm::tm) -> if h <= hm then check_possible t tm else false;; 

let check_p curr clues max x = (count_list curr) + (count_list clues) <= x && check_possible curr max;; 

let rec increase_pos curr pos =
	match curr with
	|[] -> []
	|h::t -> if pos > 0 then h::(increase_pos t (pos - 1)) else (h + 1)::(set_spaces t);;

let rec spaces_possibilities curr max clues x pos =
	if check_p (increase_pos curr pos) clues max x then curr::(spaces_possibilities (increase_pos curr pos) max clues x ((length curr)-1))
		else if pos > (-1) then spaces_possibilities curr max clues x ((pos)-1) else [curr];;

let rec possibility clues spaces x =
	match (clues, spaces) with
	|[], [] -> if x > 0 then 0::(possibility [] [] (x-1)) else []
	|(h::t), (hp::tp) -> if hp > 0 then 0::(possibility (h::t) ((hp-1)::tp) (x-1)) else 
							if h > 0 then 1::(possibility ((h-1)::t) (0::tp) (x-1)) else possibility t tp x;;

let rec check_if_viable_possibility possible_line found =
	match (possible_line, found) with
	|[], [] -> true
	|(h::t), (hf::tf) -> if hf = 0 then check_if_viable_possibility t tf else 
							if h == hf then check_if_viable_possibility t tf else false;;

let rec line_possibilities clues found x = function
	|[] -> []
	|h::t -> if (check_if_viable_possibility (possibility clues h x) found) then (possibility clues h x)::(line_possibilities clues found x t) else line_possibilities clues found x t;;

let rec line_poss clues found x = line_possibilities clues found x (spaces_possibilities (set_min clues) (set_max (get_max_space_size x (set_min clues)) clues) clues x ((length (set_min clues))-1));;  

let rec get_lines_possibilities x lines found =
	match (lines, found) with
	|[], [] -> []
	|(h::t), (hf::tf) -> (line_poss h hf x)::(get_lines_possibilities x t tf);;

let rec get_viable_lines_possibilities x lines columns = get_lines_possibilities x lines (solve_simple_box lines columns);;

let rec count_lines_possibilities = function
	|[] -> []
	|h::t -> (count h)::(count_lines_possibilities t);;

let rec get_columns x = function l -> if x > 0 then (get_heads l)::(get_columns (x - 1) (remove_heads l)) else [];;

let rec solution_found ncolumns lines_clues columns_clues possible_answer = (check_lines_solved lines_clues possible_answer) && (check_lines_solved columns_clues (get_columns ncolumns possible_answer));;

let rec set_run = function
	|[] -> []
	|h::t -> 0::(set_run t);;

let rec check_if_possibility_exists curr max =
	match (curr, max) with
	|[], [] -> true
	|(h::t), (hm::tm) -> if h <= hm then check_if_possibility_exists t tm else false;;

let rec increment_possibilities curr pos =
	match curr with
	|[] -> []
	|h::t -> if pos > 0 then h::(increment_possibilities t (pos - 1)) else (h + 1)::(set_run t);;

let rec get_from_possibilities pos = function
	|[] -> []
	|h::t -> if pos > 0 then get_from_possibilities (pos - 1) t else h;;

let rec get_possible_solution curr possibilities =
	match (curr, possibilities) with
	|[], [] -> []
	|(h::t), (hp::tp) -> (get_from_possibilities h hp)::(get_possible_solution t tp);;

let rec solve_puzzle ncolumns lines_clues columns_clues possible_lines run max pos =
	if (solution_found ncolumns lines_clues columns_clues (get_possible_solution run possible_lines)) then get_possible_solution run possible_lines else
		if (check_if_possibility_exists (increment_possibilities run pos) max) then solve_puzzle ncolumns lines_clues columns_clues possible_lines (increment_possibilities run pos) max ((length run) - 1) else
			solve_puzzle ncolumns lines_clues columns_clues possible_lines run max ((pos) - 1);;

let rec puzzle_to_solve_puzzle lines columns possibilities = solve_puzzle (count columns) lines columns possibilities (set_run possibilities) (count_lines_possibilities possibilities) ((length (set_run possibilities))-1);;

let rec puzzle = function h::t -> print_grid (puzzle_to_solve_puzzle h (get_head t) (get_viable_lines_possibilities (count (get_head t)) h (get_head t)));;