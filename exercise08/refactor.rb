# Dylan Deforrest
# CS 362 Exercise 8: Intermediate Ruby

def noun      = 2.times { puts "Noun: Cadillac" }
def verb      = 2.times { puts "Verb: Accelerate" }
def adjective = 3.times { puts "Adjective: Dark" }
def adverb    = 2.times { puts "Adverb: Confidently" }
def gerund    = 4.times { puts "Gerund: Grooving" }

commands = ["noun", "verb", "adjective", "adverb", "gerund"]

puts "Enter a command: " + commands.join(' ')
selection = gets.chomp

send(selection) if commands.include?(selection)