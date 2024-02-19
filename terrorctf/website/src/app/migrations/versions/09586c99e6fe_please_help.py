"""please help

Revision ID: 09586c99e6fe
Revises: 
Create Date: 2024-02-03 02:46:08.962868

"""
from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision = '09586c99e6fe'
down_revision = None
branch_labels = None
depends_on = None


def upgrade():
    # ### commands auto generated by Alembic - please adjust! ###
    op.create_table('problem',
    sa.Column('id', sa.Integer(), nullable=False),
    sa.Column('name', sa.String(length=100), nullable=True),
    sa.Column('description', sa.Text(), nullable=True),
    sa.Column('category', sa.String(length=50), nullable=True),
    sa.CheckConstraint("category IN ('crypto', 'web', 'pwn', 'rev', 'misc')", name='valid_problem_category'),
    sa.PrimaryKeyConstraint('id')
    )
    op.create_table('team',
    sa.Column('id', sa.Integer(), nullable=False),
    sa.Column('name', sa.String(length=50), nullable=True),
    sa.Column('shareable_id', sa.String(length=32), nullable=True),
    sa.PrimaryKeyConstraint('id'),
    sa.UniqueConstraint('name')
    )
    op.create_table('team_problems_solved',
    sa.Column('team_id', sa.Integer(), nullable=True),
    sa.Column('problem_id', sa.Integer(), nullable=True),
    sa.ForeignKeyConstraint(['problem_id'], ['problem.id'], ),
    sa.ForeignKeyConstraint(['team_id'], ['team.id'], )
    )
    op.create_table('user',
    sa.Column('id', sa.Integer(), nullable=False),
    sa.Column('username', sa.String(length=100), nullable=True),
    sa.Column('password', sa.String(length=100), nullable=True),
    sa.Column('fk_user_team_id', sa.Integer(), nullable=True),
    sa.ForeignKeyConstraint(['fk_user_team_id'], ['team.id'], ),
    sa.PrimaryKeyConstraint('id'),
    sa.UniqueConstraint('username')
    )
    # ### end Alembic commands ###


def downgrade():
    # ### commands auto generated by Alembic - please adjust! ###
    op.drop_table('user')
    op.drop_table('team_problems_solved')
    op.drop_table('team')
    op.drop_table('problem')
    # ### end Alembic commands ###
