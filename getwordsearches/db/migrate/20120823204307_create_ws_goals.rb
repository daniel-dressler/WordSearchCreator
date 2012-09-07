class CreateWsGoals < ActiveRecord::Migration
  def change
    create_table :ws_goals do |t|
      t.references :difficulty
      t.boolean :name
      t.boolean :date
      t.string :due
      t.integer :copies
      t.string :title
      t.references :set

      t.timestamps
    end
    add_index :ws_goals, :difficulty_id
    add_index :ws_goals, :set_id
  end
end
