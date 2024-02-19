import os
from pathlib import Path
import random
import tomllib
from flask import render_template, request
from app.challenges import bp
from app.models.challenges import Problem
from app.util.fileutils import copy_file, delete_folder_contents


@bp.route('/list')
def list():

    return render_template("challenges/list.html")

@bp.route('/iafijoa/load-challenges', methods=['GET', 'POST'])
def load_challenges():
    """This may be very prone to breaking. Be cautious."""

    if request.method == 'POST':
        appdir = Path(os.path.abspath(os.path.dirname(__file__)))
        srcdir = appdir.parent.absolute()
        webdir = srcdir.parent.absolute()
        rootdir = webdir.parent.absolute()

        downloads_dir = appdir / "static" / "downloads"
        problems_dir = rootdir / "problems"

        delete_folder_contents(downloads_dir)

        problems_to_add = []
        # iterate over all the categories
        for category_dir in problems_dir.glob("*/"):
            if "rev" not in category_dir.name    or \
            "web" not in category_dir.name    or \
            "pwn" not in category_dir.name    or \
            "misc" not in category_dir.name   or \
            "crypto" not in category_dir.name:
                continue
            
            # iterate over each problem in each category
            for problem_dir in category_dir.glob("*/"):
                with open(problem_dir / "challenge.toml", "rb") as f:
                    problem_toml = tomllib.load(f)
                    section_challenge = problem_toml.get("challenge")
                    section_download = problem_toml.get("download")
                    section_server = problem_toml.get("server")
                    section_netcat = section_server.get("netcat") if section_server is not None else None

                    problem_title = section_challenge.get("title")
                    problem_description_filename = section_challenge.get("description", "No description provided.")
                    problem_flag = section_challenge.get("flag")
                    problem_points = section_challenge.get("points")

                    if section_challenge  is None \
                        or problem_title  is None \
                        or problem_flag   is None \
                        or problem_points is None:
                        # TODO: Add logging that the problem was invalid
                        continue
                    
                    problem_description_file: Path = problem_dir / problem_description_filename

                    description_filename = "description" + problem_title + "_" + str(random.randint(1000, 9999))

                    # copy the file to the downloads directory
                    copy_file(
                        problem_description_file,
                        downloads_dir / description_filename
                    )
                    return "done"


                    # Problem(
                    #     name=problem_title,
                        
                    # )

