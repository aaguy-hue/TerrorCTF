from flask_login import UserMixin
from app.models.challenges import Problem
from app.extensions import db

team_problems_solved = db.Table(
    'team_problems_solved',
    db.Column('team_id', db.Integer, db.ForeignKey('team.id')),
    db.Column('problem_id', db.Integer, db.ForeignKey('problem.id')),
)

class Team(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(50), unique=True)
    shareable_id = db.Column(db.String(32))
    solved_problems = db.relationship(
        'Problem',
        secondary=team_problems_solved,
        backref=db.backref('teams_that_solved', lazy='dynamic'),
        lazy='dynamic'
    )

    def __repr__(self):
        return f'<Team "{self.name}">'


class User(UserMixin, db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(100))

    team_id = db.Column(db.Integer, db.ForeignKey('team.id'), name='fk_user_team_id')
    team = db.relationship('Team', backref='members')
