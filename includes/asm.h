/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:21:51 by yhetman           #+#    #+#             */
/*   Updated: 2019/10/30 21:53:33 by botkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define DEBUG 1

# include "../asmlib/includes/asmlib.h"

typedef struct			s_command
{
	char				*command;
	char				*args;
}						t_command;

typedef struct			s_reader
{
	int					line;
	int					sign;
}						t_reader;

typedef struct			s_writer
{
	int					cursor;
	int					command_index;
	int					curr_command;
	int					token;
	int					fd;
}						t_writer;

typedef struct			s_bytes
{
	int					first;
	int					last;
	int					size;
}						t_bytes;

typedef struct			s_token
{
	char				*name;
	int					count;
	t_bytes				byte;
}						t_token;

typedef struct			s_assembler
{
	char				**command;
	char				***stored;
	int					count;
	t_token				*tokens;
	t_op				*options;
}						t_assembler;

int						go_to_assembler(char *file);
int						great_initialization(t_assembler *a, int lines,
						char *line);
int						great_freeing(t_assembler *ass, char *line);
int						store_all_token_details(t_assembler *ass);
int						file_checker(t_assembler *ass, t_header *head);
int						get_command_info(t_assembler *ass, int count);
int						get_command_arguments(t_assembler *ass, t_command
						*command, int index, int i);
int						rewrite_file(t_assembler *ass, t_header *head,
						int lines, char *file);
int						catch_tokens(t_assembler *ass);
void					print_t_assembler(t_assembler *ass);
void					init_g_o(t_assembler *ass);
int						octet(long long numb);
char					*del_space(char *str);
t_header				*init_t_header(void);
t_reader				*init_t_reader(void);
t_assembler				*init_t_assembler(void);
int						clear_t_reader(t_reader *reader);
int						clear_t_header(t_header *header);
int						clear_t_assembler(t_assembler *ass);
int						writing_process(t_assembler *ass, t_writer *writer,
						char **buffer, int fd);
void					write_direct_indirect(t_assembler *ass,
						t_writer *writer, char **buffer, int i);
#endif
