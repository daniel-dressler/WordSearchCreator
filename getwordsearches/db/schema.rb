# encoding: UTF-8
# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended to check this file into your version control system.

ActiveRecord::Schema.define(:version => 20120823204827) do

  create_table "word_search_sets", :force => true do |t|
    t.integer  "prototype_id"
    t.integer  "goal_id"
    t.integer  "swears_id"
    t.integer  "words_id"
    t.integer  "grids_id"
    t.integer  "alphabet_id"
    t.datetime "created_at",   :null => false
    t.datetime "updated_at",   :null => false
  end

  add_index "word_search_sets", ["alphabet_id"], :name => "index_word_search_sets_on_alphabet_id"
  add_index "word_search_sets", ["goal_id"], :name => "index_word_search_sets_on_goal_id"
  add_index "word_search_sets", ["grids_id"], :name => "index_word_search_sets_on_grids_id"
  add_index "word_search_sets", ["prototype_id"], :name => "index_word_search_sets_on_prototype_id"
  add_index "word_search_sets", ["swears_id"], :name => "index_word_search_sets_on_swears_id"
  add_index "word_search_sets", ["words_id"], :name => "index_word_search_sets_on_words_id"

  create_table "word_searches", :force => true do |t|
    t.integer  "width"
    t.integer  "height"
    t.string   "board"
    t.datetime "created_at", :null => false
    t.datetime "updated_at", :null => false
  end

  create_table "word_selections", :force => true do |t|
    t.string   "words"
    t.datetime "created_at", :null => false
    t.datetime "updated_at", :null => false
  end

  create_table "ws_alphas", :force => true do |t|
    t.string   "chars"
    t.integer  "set_id"
    t.datetime "created_at", :null => false
    t.datetime "updated_at", :null => false
  end

  add_index "ws_alphas", ["set_id"], :name => "index_ws_alphas_on_set_id"

  create_table "ws_goals", :force => true do |t|
    t.integer  "difficulty_id"
    t.boolean  "name?"
    t.boolean  "date?"
    t.string   "due"
    t.string   "title"
    t.integer  "set_id"
    t.datetime "created_at",    :null => false
    t.datetime "updated_at",    :null => false
  end

  add_index "ws_goals", ["difficulty_id"], :name => "index_ws_goals_on_difficulty_id"
  add_index "ws_goals", ["set_id"], :name => "index_ws_goals_on_set_id"

  create_table "ws_grids", :force => true do |t|
    t.string   "grid"
    t.integer  "set_id"
    t.datetime "created_at", :null => false
    t.datetime "updated_at", :null => false
  end

  add_index "ws_grids", ["set_id"], :name => "index_ws_grids_on_set_id"

  create_table "ws_prototypes", :force => true do |t|
    t.integer  "height"
    t.integer  "width"
    t.integer  "seed"
    t.integer  "set_id"
    t.datetime "created_at", :null => false
    t.datetime "updated_at", :null => false
  end

  add_index "ws_prototypes", ["set_id"], :name => "index_ws_prototypes_on_set_id"

  create_table "ws_word_lists", :force => true do |t|
    t.string   "words"
    t.integer  "set_id"
    t.datetime "created_at", :null => false
    t.datetime "updated_at", :null => false
  end

  add_index "ws_word_lists", ["set_id"], :name => "index_ws_word_lists_on_set_id"

end
